#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){

    pid_t pid = fork();

    if(pid < 0){
        fprintf(stderr, "Fork failed");
    }else if(pid == 0){
        printf("[Child] : My PID = %d\n", getpid());
        printf("[Child] : My parent PID = %d\n", getppid());
    }else{
        printf("[Parent] : My PID = %d\n", getpid());
        printf("[Parent] : My child PID = %d\n", pid);

        wait(NULL);
    }

    return 0;
}
