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

