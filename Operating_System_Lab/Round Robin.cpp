#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    vector<int> at(n), bt(n), rt(n), ct(n), tat(n), wt(n), pid(n);
    vector<bool> inQueue(n, false);

    // Input
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter AT and BT for P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];
    }

    // Sort processes by Arrival Time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(rt[j], rt[j + 1]);
                swap(pid[j], pid[j + 1]);
            }
        }
    }

    queue<int> q;
    int current_time = 0, completed = 0;
    vector<string> gantt;

    // Check if any process arrives exactly at time 0
    for (int j = 0; j < n; j++)
    {
        if (at[j] <= current_time && !inQueue[j])
        {
            q.push(j);
            inQueue[j] = true;
        }
    }

    while (completed < n)
    {
        if (q.empty())
        {
            // FIX: Explicitly log idle time in the Gantt chart
            gantt.push_back("IDLE");
            current_time++;

            for (int j = 0; j < n; j++)
            {
                if (at[j] <= current_time && !inQueue[j])
                {
                    q.push(j);
                    inQueue[j] = true;
                }
            }
            continue;
        }

        int i = q.front();
        q.pop();

        int exec_time = min(quantum, rt[i]);

        // Per unit time Gantt
        for (int t = 0; t < exec_time; t++)
        {
            gantt.push_back("P" + to_string(pid[i]));
        }

        rt[i] -= exec_time;
        current_time += exec_time;

        // Add new arrivals (FCFS order maintained because sorted by AT initially)
        for (int j = 0; j < n; j++)
        {
            if (at[j] <= current_time && !inQueue[j])
            {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // Put the running process back in the queue if it's not finished
        if (rt[i] > 0)
        {
            q.push(i);
        }
        else
        {
            ct[i] = current_time;
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
            completed++;
        }
    }

    // FIX: Sort back by PID to display the final table cleanly
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pid[j] > pid[j + 1])
            {
                swap(pid[j], pid[j + 1]);
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(ct[j], ct[j + 1]);
                swap(tat[j], tat[j + 1]);
                swap(wt[j], wt[j + 1]);
            }
        }
    }

    // Gantt Chart
    cout << "\nGantt Chart (Per Unit Time):\n";
    for (auto &p : gantt)
        cout << "| " << p << " ";
    cout << "|\n";

    // Output
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;

        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Added fixed precision for cleaner decimal output
    cout << fixed << setprecision(2);
    cout << "\nAverage WT = " << total_wt / n << endl;
    cout << "Average TAT = " << total_tat / n << endl;

    return 0;
}