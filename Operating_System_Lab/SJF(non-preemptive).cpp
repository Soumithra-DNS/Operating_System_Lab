#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], ct[n], tat[n], wt[n], pid[n];
    bool done[n] = {false};

    // Input
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter AT and BT for P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
    }

    int completed = 0, current_time = 0;

    vector<string> gantt; // store execution order

    while (completed < n)
    {
        int idx = -1;
        int min_bt = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && at[i] <= current_time)
            {
                if (idx == -1 ||
                    bt[i] < min_bt ||
                    (bt[i] == min_bt && at[i] < at[idx]))
                {
                    min_bt = bt[i];
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

        // Add to Gantt Chart
        gantt.push_back("P" + to_string(pid[idx]));

        // Execute process
        ct[idx] = current_time + bt[idx];
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        current_time = ct[idx];
        done[idx] = true;
        completed++;
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n";
    for (auto &p : gantt)
        cout << "| " << p << " ";
    cout << "|\n";

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

    cout << "\nAverage WT = " << total_wt / n << endl;
    cout << "Average TAT = " << total_tat / n << endl;

    return 0;
}


/*
5
2 6
5 2
1 8
0 3
4 4
*/