#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n], pid[n];

    // Input
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter AT and BT for P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];   // remaining time
    }

    int completed = 0, current_time = 0;

    // SRTF Logic (Preemptive)
    while (completed < n)
    {
        int idx = -1;
        int min_rt = 1e9;

        // Find process with minimum remaining time
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= current_time && rt[i] > 0 && rt[i] < min_rt)
            {
                min_rt = rt[i];
                idx = i;
            }
        }

        // If no process available → CPU idle
        if (idx == -1)
        {
            current_time++;
            continue;
        }

        // Execute for 1 unit
        rt[idx]--;
        current_time++;

        // If process finished
        if (rt[idx] == 0)
        {
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        }
    }

    // Output
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    // Average
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    cout << "\nAverage WT = " << total_wt / n << endl;
    cout << "Average TAT = " << total_tat / n << endl;

    return 0;
}