#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child (PID %d) printing: ", getpid());
        for (int i = 6; i <= 10; i++)
        {
            printf("%d ", i);
        }
        printf("\n");
    }
    else
    {
        printf("Parent (PID %d) printing: ", getpid());
        for (int i = 1; i <= 5; i++)
        {
            printf("%d ", i);
        }
        printf("\n");

        wait(NULL);
        printf("Parent: child has finished.\n");
    }

    return 0;
}