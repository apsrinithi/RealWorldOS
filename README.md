# The Sleeping Barber Problem - Synchronization Simulation in C

A classic multi-threaded synchronization simulation of the **Sleeping Barber Problem** using POSIX threads (`pthreads`), semaphores (`semaphore.h`), and mutual exclusion locks (`pthread_mutex_t`) in C.

---

## 🚀 About the Project
The Sleeping Barber Problem is a classic inter-process communication and synchronization challenge in operating systems. It models a barbershop with:
* One barber and one barber chair.
* A waiting room with a fixed number of chairs (`NUM_CHAIRS`).
* Multiple customer threads arriving at random intervals.

### How it Works:
* If there are no customers, the barber goes to sleep in the barber chair.
* When a customer arrives and a waiting chair is available, they sit down and wake up the barber.
* If all waiting chairs are occupied, the incoming customer leaves the shop.
* Once the barber finishes a haircut, they check for the next waiting customer.

---

## 🛠️ Synchronization Mechanisms Used
1. **Mutex Lock (`pthread_mutex_t`)**: Protects the shared `waiting` counter when customers enter or leave the waiting room.
2. **Customers Semaphore (`sem_t customers`)**: Counts waiting customers and acts as the wakeup signal for the sleeping barber.
3. **Barber Semaphore (`sem_t barber`)**: Signals when the barber is ready to begin a haircut for a specific customer.

---

# Deadlock Detection Algorithm in C

A robust C program that simulates operating system resource allocation states, detects active deadlocks using a graph reduction/safety algorithm (similar to the Banker's safety algorithm) for multiple resource instances, and suggests safe process recovery strategies.

---

## 🚀 About the Project
In multi-threaded or multi-process operating systems, deadlocks can occur when processes are mutually blocked, each holding resources and waiting for others to release them. 

This program models system state using:
* **Allocation Matrix**: Resources currently allocated to each process.
* **Request Matrix**: Additional resources currently requested by each process.
* **Available Vector**: Unallocated resources currently available in the system.

It analyzes these matrices to find cycles of dependency and identifies which processes are deadlocked, offering a remediation rollback plan.

---

## 🛠️ Key Features
* **Multi-Resource Support**: Handles multiple instances of various resource types.
* **Deadlock Identification**: Scans and pinpoints specific deadlocked processes (e.g., Process P0, P1, P2).
* **Automated Recovery / Rollback Strategy**: Suggests the optimal process to terminate or roll back based on resource weight to break the circular wait safely.

---

# Producer-Consumer Problem Simulation in C

A classic multi-threaded synchronization solution implementing the **Producer-Consumer problem** using POSIX threads (`pthreads`), semaphores (`semaphore.h`), and mutual exclusion locks (`pthread_mutex_t`) in C.

---

## 🚀 About the Project
In concurrent programming, the Producer-Consumer problem is a standard challenge where multiple producer threads generate data items and place them into a fixed-size shared buffer, while multiple consumer threads remove and process those items. 

This implementation ensures safe concurrent execution by preventing:
* **Race conditions** when modifying the shared buffer or index pointers.
* **Buffer overflow** (producers waiting if the buffer is full).
* **Buffer underflow** (consumers waiting if the buffer is empty).

---

## 🛠️ Synchronization Mechanisms Used
1. **Mutex Lock (`pthread_mutex_t`)**: Protects the critical section where shared buffer indexes (`in` and `out`) are updated.
2. **Empty Semaphore (`sem_t empty`)**: Tracks available empty slots in the circular buffer (initialized to `BUFFER_SIZE`).
3. **Full Semaphore (`sem_t full`)**: Tracks filled slots containing ready items (initialized to `0`).

---

