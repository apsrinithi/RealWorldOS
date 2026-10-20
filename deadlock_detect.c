#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m; 
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int request[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    printf("Enter number of resource types: ");
    if (scanf("%d", &m) != 1) return 1;

    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Request Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources Vector (size %d):\n", m);
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    for (int i = 0; i < n; i++) {
        bool has_allocated = false;
        for (int j = 0; j < m; j++) {
            if (allocation[i][j] > 0) {
                has_allocated = true;
                break;
            }
        }
        finish[i] = !has_allocated;
    }
    bool progress;
    do {
        progress = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    } while (progress);

    bool deadlock_detected = false;
    printf("\n--- Deadlock Detection Results ---\n");
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            if (!deadlock_detected) {
                printf("Deadlock Detected! The following processes are deadlocked:\n");
                deadlock_detected = true;
            }
            printf(" -> Process P%d\n", i);
        }
    }

    if (!deadlock_detected) {
        printf("No deadlock detected. The system is in a safe state.\n");
    } else {
        printf("\n--- Suggested Rollback Recovery ---\n");
        printf("To break the deadlock, consider terminating or rolling back one of the deadlocked processes:\n");
        
        int candidate = -1;
        int max_allocated = -1;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int total_allocated = 0;
                for (int j = 0; j < m; j++) {
                    total_allocated += allocation[i][j];
                }
                if (total_allocated > max_allocated) {
                    max_allocated = total_allocated;
                    candidate = i;
                }
            }
        }
        printf("Recommended process to terminate/rollback: Process P%d (holds %d resource units)\n", candidate, max_allocated);
    }

    return 0;
}