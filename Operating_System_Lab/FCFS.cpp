#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], ct[n], tat[n], wt[n], pid[n];

    // Input (compact style)
    cout << "Enter Arrival Time and Burst Time:\n";
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;   // Process ID
        cin >> at[i] >> bt[i];
    }

    // Sort by Arrival Time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(pid[j], pid[j + 1]);
            }
        }
    }

    // FCFS Calculation
    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        // Handle CPU idle time
        if (current_time < at[i])
            current_time = at[i];

        ct[i] = current_time + bt[i];   // Completion Time
        tat[i] = ct[i] - at[i];        // Turnaround Time
        wt[i] = tat[i] - bt[i];        // Waiting Time

        current_time = ct[i];
    }

    // Output
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    // Average Waiting Time
    float total_wt = 0;
    for (int i = 0; i < n; i++)
        total_wt += wt[i];

    cout << "\nAverage Waiting Time = " << total_wt / n << endl;

    return 0;
}

/*
5
4 2
0 3
2 1
1 4
3 2
*/