#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t child1, child2;

    // ---- First Child ----
    child1 = fork();

    if (child1 < 0) {
        fprintf(stderr, "Fork 1 failed!\n");
        return 1;
    }

    if (child1 == 0) {
        // Child 1 process
        printf("[Child 1] PID: %d | PPID: %d\n", getpid(), getppid());
        return 0;   // Important: stop here
    }

    // ---- Second Child (only parent reaches here) ----
    child2 = fork();

    if (child2 < 0) {
        fprintf(stderr, "Fork 2 failed!\n");
        return 1;
    }

    if (child2 == 0) {
        // Child 2 process
        printf("[Child 2] PID: %d | PPID: %d\n", getpid(), getppid());
        return 0;   // stop here
    }

    // ---- Parent Process ----
    printf("[Parent] PID: %d\n", getpid());
    printf("   |-- Child 1 PID: %d\n", child1);
    printf("   |-- Child 2 PID: %d\n", child2);

    // Wait for both children
    wait(NULL);
    wait(NULL);

    printf("[Parent] Both children finished.\n");

    return 0;
}