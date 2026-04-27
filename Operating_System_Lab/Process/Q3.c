#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t child1, child2;

    // --- প্রথম চাইল্ড তৈরি করা হচ্ছে ---
    child1 = fork();

    if (child1 < 0) { 
        fprintf(stderr, "Fork 1 failed!\n"); 
        return 1; 
    }

    if (child1 == 0) {
        // এই ব্লকটি শুধুমাত্র Child 1 এর জন্য
        printf("Child 1 | PID: %d | PPID: %d\n", getpid(), getppid());
        return 0; // চাইল্ড ১ এর কাজ শেষ, সে যেন দ্বিতীয় fork() এ না যায়
    }

    // --- দ্বিতীয় চাইল্ড তৈরি করা হচ্ছে (শুধুমাত্র প্যারেন্ট এখানে পৌঁছাবে) ---
    child2 = fork();

    if (child2 < 0) { 
        fprintf(stderr, "Fork 2 failed!\n"); 
        return 1; 
    }

    if (child2 == 0) {
        // এই ব্লকটি শুধুমাত্র Child 2 এর জন্য
        printf("Child 2 | PID: %d | PPID: %d\n", getpid(), getppid());
        return 0; // চাইল্ড ২ এর কাজ শেষ
    }

    // --- প্যারেন্ট প্রসেসের কাজ ---
    printf("Parent  | PID: %d\n", getpid());
    printf("  |-- Child1 PID: %d\n", child1);
    printf("  |-- Child2 PID: %d\n", child2);

    // দুটি চাইল্ডের জন্যই অপেক্ষা করা হচ্ছে
    wait(NULL); 
    wait(NULL); 

    printf("Parent: both children have finished.\n");

    return 0;
}