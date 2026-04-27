#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }
    else if (pid == 0) {
        // Child process: prints 6–10
        cout << "Child (PID " << getpid() << ") printing: ";
        for (int i = 6; i <= 10; i++)
            cout << i << " ";
        cout << endl;
    }
    else {
        // Parent process: prints 1–5
        cout << "Parent (PID " << getpid() << ") printing: ";
        for (int i = 1; i <= 5; i++)
            cout << i << " ";
        cout << endl;

        wait(nullptr); // Reap child to avoid zombie
        cout << "Parent: child has finished." << endl;
    }
    return 0;
}