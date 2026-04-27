#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n], pid[n];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter AT and BT for P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];
    }

    int completed = 0, current_time = 0;

    vector<string> gantt;

    while (completed < n)
    {
        int idx = -1;
        int min_rt = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= current_time && rt[i] > 0)
            {
                if (idx == -1 ||
                    rt[i] < min_rt ||
                    (rt[i] == min_rt && at[i] < at[idx]))
                {
                    min_rt = rt[i];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            current_time++;
            continue;
        }

        rt[idx]--;
        gantt.push_back("P" + to_string(pid[idx]));
        current_time++;

        if (rt[idx] == 0)
        {
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        }
    }

    // Gantt Chart with time
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < gantt.size(); i++)
        cout << "| " << gantt[i] << " ";
    cout << "|\n";

    cout << "0 ";
    for (int i = 1; i <= gantt.size(); i++)
        cout << i << " ";

    // Output
    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";
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
0 7
2 4
4 1
5 4
6 3
*/