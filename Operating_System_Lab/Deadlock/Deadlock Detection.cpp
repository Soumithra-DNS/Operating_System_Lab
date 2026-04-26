#include <iostream>
#include <vector>
using namespace std;

bool detectDeadlock(vector<vector<int>> &alloc,
                    vector<vector<int>> &request,
                    vector<int> &avail,
                    int n, int m)
{
    vector<bool> finish(n, false);
    vector<int> work = avail;

    int count = 0;

    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canExecute = true;

                // Check if Request <= Work
                for (int j = 0; j < m; j++)
                {
                    if (request[i][j] > work[j])
                    {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute)
                {
                    // Release resources
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += alloc[i][j];
                    }

                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found)
            break; // no process can execute
    }

    // Check deadlock
    bool deadlock = false;

    cout << "Deadlocked Processes: ";
    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            cout << "P" << i;
            deadlock = true;
        }
    }

    if (!deadlock)
        cout << "None (No Deadlock)";

    cout << endl;

    return deadlock;
}

int main()
{
    int n = 5; // processes
    int m = 3; // resources

    // Allocation Matrix
    vector<vector<int>> alloc = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 3},
        {2, 1, 1},
        {0, 0, 2}};

    // Request Matrix
    vector<vector<int>> request = {
        {0, 0, 0},
        {2, 0, 2},
        {0, 0, 1},
        {1, 0, 0},
        {0, 0, 2}};

    // Available Resources
    vector<int> avail = {0, 0, 0};

    detectDeadlock(alloc, request, avail, n, m);

    return 0;
}