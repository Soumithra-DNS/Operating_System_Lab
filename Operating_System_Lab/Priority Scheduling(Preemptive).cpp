#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n], pr[n], ct[n], tat[n], wt[n], pid[n];

    // Input
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter AT, BT, Priority for P" << i + 1 << ": ";
        cin >> at[i] >> bt[i] >> pr[i];
        rt[i] = bt[i];
    }

    int completed = 0, current_time = 0;

    // Preemptive Priority Scheduling
    while (completed < n)
    {
        int idx = -1;
        int highest_priority = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= current_time && rt[i] > 0)
            {
                if (idx == -1 ||
                    pr[i] < highest_priority ||
                    (pr[i] == highest_priority && at[i] < at[idx]))
                {
                    highest_priority = pr[i];
                    idx = i;
                }
            }
        }

        // CPU Idle
        if (idx == -1)
        {
            current_time++;
            continue;
        }

        // Execute for 1 unit
        rt[idx]--;
        current_time++;

        // If finished
        if (rt[idx] == 0)
        {
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        }
    }

    // Output
    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << pr[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;

        total_wt += wt[i];
        total_tat += tat[i];
    }

    cout << "\nAverage WT = " << total_wt / n << endl;
    cout << "Average TAT = " << total_tat / n << endl;

    return 0;
}