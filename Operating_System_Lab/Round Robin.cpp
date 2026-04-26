#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n], pid[n];
    bool inQueue[n] = {false};

    // Input
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter AT and BT for P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];
    }

    queue<int> q;

    int current_time = 0, completed = 0;

    // Find first arriving process
    int first = 0;
    for (int i = 1; i < n; i++)
    {
        if (at[i] < at[first])
            first = i;
    }

    current_time = at[first];
    q.push(first);
    inQueue[first] = true;

    vector<string> gantt; // for Gantt chart

    while (!q.empty())
    {
        int i = q.front();
        q.pop();

        // Execute process
        int exec_time = min(quantum, rt[i]);

        // Add to Gantt chart
        gantt.push_back("P" + to_string(pid[i]));

        rt[i] -= exec_time;
        current_time += exec_time;

        // Check new arrivals
        for (int j = 0; j < n; j++)
        {
            if (at[j] <= current_time && !inQueue[j] && rt[j] > 0)
            {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // If not finished → push back
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