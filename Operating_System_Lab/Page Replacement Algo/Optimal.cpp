#include <iostream>
using namespace std;

int main()
{
    int n, fn;
    cout << "Enter number of pages: ";
    cin >> n;

    int pg[n];
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++)
        cin >> pg[i];

    cout << "Enter number of frames: ";
    cin >> fn;

    int fr[fn];

    // Initialize frames with -1
    for (int i = 0; i < fn; i++)
        fr[i] = -1;

    int hit = 0;

    for (int i = 0; i < n; i++)
    {
        bool found = false;

        // Check HIT
        for (int j = 0; j < fn; j++)
        {
            if (fr[j] == pg[i])
            {
                hit++;
                found = true;
                break;
            }
        }

        if (found)
            continue;

        // Check empty frame
        bool empty = false;
        for (int j = 0; j < fn; j++)
        {
            if (fr[j] == -1)
            {
                fr[j] = pg[i];
                empty = true;
                break;
            }
        }

        if (empty)
            continue;

        // Find replacement (farthest use)
        int farthest = -1, index = -1;

        for (int j = 0; j < fn; j++)
        {
            int k;
            for (k = i + 1; k < n; k++)
            {
                if (fr[j] == pg[k])
                {
                    if (k > farthest)
                    {
                        farthest = k;
                        index = j;
                    }
                    break;
                }
            }

            // If not used again
            if (k == n)
            {
                index = j;
                break;
            }
        }

        fr[index] = pg[i];
    }

    cout << "\nHits = " << hit << endl;
    cout << "Misses = " << (n - hit) << endl;

    return 0;
}