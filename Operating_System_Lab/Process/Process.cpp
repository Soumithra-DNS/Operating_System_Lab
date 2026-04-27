#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    pid_t childPid = fork(); // Create a child process

    if (childPid < 0) {
        // fork() failed
        cerr << "Fork failed!" << endl;
        return 1;
    }
    else if (childPid == 0) {
        // --- CHILD PROCESS ---
        cout << "[Child]  My PID  : " << getpid()  << endl;
        cout << "[Child]  My PPID : " << getppid() << endl;
    }
    else {
        // --- PARENT PROCESS ---
        cout << "[Parent] My PID      : " << getpid()  << endl;
        cout << "[Parent] Child's PID : " << childPid  << endl;
        wait(nullptr); // Wait for child to finish; prevents zombie process
    }
    return 0;
}