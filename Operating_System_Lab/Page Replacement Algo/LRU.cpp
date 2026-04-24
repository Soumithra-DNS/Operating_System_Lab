#include <iostream>
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

    int fr[capacity];
    int last_used[capacity];

    // Initialize
    for (int i = 0; i < capacity; i++)
    {
        fr[i] = -1;
        last_used[i] = -1;
    }

    int time = 0, page_faults = 0;

    for (int i = 0; i < n; i++)
    {
        bool found = false;

        // Check HIT
        for (int j = 0; j < capacity; j++)
        {
            if (fr[j] == pages[i])
            {
                found = true;
                last_used[j] = time++; // update recent use
                break;
            }
        }

        if (found)
            continue;

        // Page FAULT
        page_faults++;

        int idx = -1;

        // Check empty frame
        for (int j = 0; j < capacity; j++)
        {
            if (fr[j] == -1)
            {
                idx = j;
                break;
            }
        }

        // If no empty frame → find LRU
        if (idx == -1)
        {
            int lru = 1e9;
            for (int j = 0; j < capacity; j++)
            {
                if (last_used[j] < lru)
                {
                    lru = last_used[j];
                    idx = j;
                }
            }
        }

        // Replace page
        fr[idx] = pages[i];
        last_used[idx] = time++;
    }

    cout << "\nTotal Page Faults = " << page_faults << endl;

    return 0;
}

