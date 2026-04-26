#include <iostream>
#include <queue>
#include <set>
using namespace std;

int main()
{
    int n, capacity;

    cout << "Enter number of pages: ";
    cin >> n;

    int pages[n];
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter frame capacity: ";
    cin >> capacity;

    set<int> s;       // check presence
    queue<int> q;     // FIFO order

    int page_faults = 0, page_hits = 0;

    for (int i = 0; i < n; i++)
    {
        // HIT case
        if (s.find(pages[i]) != s.end())
        {
            page_hits++;
        }
        else
        {
            // FAULT case
            if (s.size() == capacity)
            {
                int val = q.front();
                q.pop();
                s.erase(val);
            }

            s.insert(pages[i]);
            q.push(pages[i]);
            page_faults++;
        }
    }

    cout << "\nPage Hits = " << page_hits << endl;
    cout << "Page Faults = " << page_faults << endl;

    return 0;
}