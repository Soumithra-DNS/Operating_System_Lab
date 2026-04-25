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

    set<int> s;       // to check presence
    queue<int> q;     // FIFO order

    int page_faults = 0;

    for (int i = 0; i < n; i++)
    {
        // If page not present → page fault
        if (s.find(pages[i]) == s.end())
        {
            // If memory full → remove oldest page
            if (s.size() == capacity)
            {
                int val = q.front();
                q.pop();
                s.erase(val);
            }

            // Insert new page
            s.insert(pages[i]);
            q.push(pages[i]);
            page_faults++;
        }
    }

    cout << "\nTotal Page Faults = " << page_faults << endl;

    return 0;
}