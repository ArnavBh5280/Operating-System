#include <iostream>
#include <climits> // For INT_MAX
using namespace std;

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    fill(allocation, allocation + n, -1); // Initialize all allocations to -1 (not allocated)

    for (int i = 0; i < n; i++) {
        int worstIndex = -1;

        // Find the block that worst fits the process
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex]) {
                    worstIndex = j;
                }
            }
        }

        // Allocate the block if found
        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
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
