#include <iostream>
#include <climits> // For INT_MAX
using namespace std;

void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    fill(allocation, allocation + n, -1); // Initialize all allocations to -1 (not allocated)
    int lastAllocated = 0; // Start from the beginning of the block array

    for (int i = 0; i < n; i++) {
        int j = lastAllocated;
        bool allocated = false;

        // Traverse blocks circularly starting from the last allocated block
        do {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastAllocated = j;
                allocated = true;
                break;
            }
            j = (j + 1) % m;
        } while (j != lastAllocated); // Stop if we return to the starting point

        if (!allocated) {
            lastAllocated = (lastAllocated + 1) % m; // Move to the next block
        }
    }

    // Print allocation result
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated\n";
    }
}
