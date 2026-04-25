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

    int frame[capacity], freq[capacity], loadedAt[capacity];

    // Initialize
    for (int i = 0; i < capacity; i++)
    {
        frame[i] = -1;
        freq[i] = 0;
        loadedAt[i] = -1;
    }

    int pageFaults = 0;

    for (int i = 0; i < n; i++)
    {
        bool found = false;

        // Check HIT
        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == pages[i])
            {
                freq[j]++;   // increase frequency
                found = true;
                break;
            }
        }

        if (found)
            continue;

        // PAGE FAULT
        pageFaults++;

        int pos = -1;

        // Check empty frame
        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == -1)
            {
                pos = j;
                break;
            }
        }

        // If full → find LFU
        if (pos == -1)
        {
            int minFreq = freq[0];
            pos = 0;

            for (int j = 1; j < capacity; j++)
            {
                if (freq[j] < minFreq)
                {
                    minFreq = freq[j];
                    pos = j;
                }
                else if (freq[j] == minFreq && loadedAt[j] < loadedAt[pos])
                {
                    pos = j; // tie-breaker: oldest
                }
            }
        }

        // Replace page
        frame[pos] = pages[i];
        freq[pos] = 1;
        loadedAt[pos] = i;
    }

    cout << "\nTotal Page Faults = " << pageFaults << endl;

    return 0;
}