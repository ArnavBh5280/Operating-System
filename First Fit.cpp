#include <iostream>
#include <vector>
using namespace std;

void firstFit(vector<int>& blockSize, int m, vector<int>& processSize, int n) {
    // Array to store allocation of block to process
    vector<int> allocation(n, -1);

    // Pick each process and allocate the first suitable block
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate block j to process i
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break; // Break once a block is allocated
            }
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}
