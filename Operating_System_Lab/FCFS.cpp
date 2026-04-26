#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], ct[n], tat[n], wt[n], pid[n];

    cout << "Enter Arrival Time and Burst Time:\n";
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
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

    int current_time = 0;

    // FCFS Calculation
    for (int i = 0; i < n; i++)
    {
        if (current_time < at[i])
            current_time = at[i];

        ct[i] = current_time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        current_time = ct[i];
    }

    // Output Table
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;

        total_wt += wt[i];
        total_tat += tat[i];
    }

    cout << "\nAverage Waiting Time = " << total_wt / n << endl;
    cout << "Average Turnaround Time = " << total_tat / n << endl;

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