#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_STUDENTS 10

sem_t chairs_sem;
sem_t students_sem;
sem_t ta_sem;

void* ta_func(void* arg) {
    unsigned int seed = time(NULL);
    while (1) {
        sem_wait(&students_sem);
        sem_post(&ta_sem);
        int help_time = rand_r(&seed) % 3 + 1;
        printf("TA is helping a student for %d seconds.\n", help_time);
        sleep(help_time);
        printf("TA finished helping.\n");
    }
    return NULL;
}

void* student_func(void* arg) {
    int id = *(int*)arg;
    unsigned int seed = time(NULL) ^ id;
    while (1) {
        if (sem_trywait(&chairs_sem) == 0) {
            printf("Student %d is waiting.\n", id);
            sem_post(&students_sem);
            sem_wait(&ta_sem);
            sem_post(&chairs_sem);
            printf("Student %d is getting help.\n", id);
            int time_away = rand_r(&seed) % 10 + 1;
            sleep(time_away);
        } else {
            printf("Student %d will try again later.\n", id);
            int wait_time = rand_r(&seed) % 5 + 1;
            sleep(wait_time);
        }
    }
    return NULL;
}

int main() {
    pthread_t ta_thread;
    pthread_t student_threads[NUM_STUDENTS];
    int student_ids[NUM_STUDENTS];

    sem_init(&chairs_sem, 0, 5);
    sem_init(&students_sem, 0, 0);
    sem_init(&ta_sem, 0, 0);

    pthread_create(&ta_thread, NULL, ta_func, NULL);

    for (int i = 0; i < NUM_STUDENTS; i++) {
        student_ids[i] = i;
        pthread_create(&student_threads[i], NULL, student_func, &student_ids[i]);
    }

    pthread_join(ta_thread, NULL);
    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(student_threads[i], NULL);
    }

    sem_destroy(&chairs_sem);
    sem_destroy(&students_sem);
    sem_destroy(&ta_sem);

    return 0;
}