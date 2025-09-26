# TA-Student Synchronization Simulation

This program simulates the "Teaching Assistant" problem, a classic concurrency and synchronization challenge analogous to the **Sleeping Barber Problem**. It uses pthreads and semaphores in C to manage the interaction between a single TA and multiple students who require help. This project was created for an Operating Systems assignment at AUT.

## The Problem Scenario

-   A Teaching Assistant (TA) has an office with a limited number of waiting chairs (5 in this simulation).
-   If the TA is free and a student arrives, the TA helps the student immediately.
-   If the TA is busy, arriving students sit in a free chair to wait.
-   If all chairs are occupied, any new student who arrives will leave and come back to try again later.
-   If the TA is free and no students are waiting, the TA "sleeps" (waits).

## Key Concepts Demonstrated

-   **Process Synchronization:** Using semaphores to coordinate complex interactions between multiple threads.
-   **Semaphores:** Applying counting semaphores and binary semaphores for mutual exclusion and signaling.
-   **Producer-Consumer Problem:** This simulation is a variant of the classic producer-consumer problem, where students "produce" requests for help and the TA "consumes" them.
-   **Concurrency:** Managing multiple student threads and a TA thread operating at the same time.

## Technologies Used

-   **Language:** C
-   **Compiler:** GCC
-   **Core Libraries:** `pthread.h`, `semaphore.h`

## How to Compile and Run

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/SadraaF/ta-student-simulation.git
    cd ta-student-simulation
    ```
2.  **Compile the code:**
    The `-lpthread` flag is required.
    ```bash
    gcc main.c -o simulation -lpthread
    ```
    *Note: On Windows, the `rand_r` function is not available. You may need to change it to `rand_s` or a similar alternative.*

3.  **Run the program:**
    ```bash
    ./simulation
    ```

## Synchronization Logic

The simulation is coordinated using three semaphores:
-   `chairs_sem`: A counting semaphore that represents the number of available chairs in the waiting area.
-   `students_sem`: A binary semaphore that students use to signal the TA that someone is ready for help.
-   `ta_sem`: A binary semaphore that the TA uses to signal that they are ready to help the next student.
