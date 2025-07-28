#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to simulate Memory Variable Partitioning (MVT)
void simulateMVT(int totalMemory, vector<int> processSizes) {
    int freeMemory = totalMemory;
    vector<int> allocations(processSizes.size(), -1); // To store allocated memory
    int totalProcesses = processSizes.size();

    cout << "\n--- MVT Simulation ---\n";
    for (int i = 0; i < totalProcesses; i++) {
        if (processSizes[i] <= freeMemory) {
            allocations[i] = totalMemory - freeMemory; // Allocate memory starting from 0
            freeMemory -= processSizes[i];
            cout << "Process " << i + 1 << " allocated " << processSizes[i] << "KB at location " 
                 << allocations[i] << "\n";
        } else {
            cout << "Process " << i + 1 << " of size " << processSizes[i] << "KB could not be allocated (insufficient memory).\n";
        }
    }
    cout << "Remaining free memory: " << freeMemory << "KB\n";
}

// Function to simulate Memory Fixed Partitioning (MFT)
void simulateMFT(int totalMemory, int partitionSize, vector<int> processSizes) {
    int numPartitions = totalMemory / partitionSize;
    vector<int> allocations(numPartitions, -1); // To store process IDs for each partition
    vector<int> internalFragmentation(numPartitions, 0);
    int totalProcesses = processSizes.size();
    int externalFragmentation = 0;

    cout << "\n--- MFT Simulation ---\n";
    for (int i = 0; i < totalProcesses; i++) {
        bool allocated = false;
        for (int j = 0; j < numPartitions; j++) {
            if (allocations[j] == -1 && processSizes[i] <= partitionSize) {
                allocations[j] = i;
                internalFragmentation[j] = partitionSize - processSizes[i];
                cout << "Process " << i + 1 << " of size " << processSizes[i] 
                     << "KB allocated to partition " << j + 1 
                     << " (Internal Fragmentation: " << internalFragmentation[j] << "KB)\n";
                allocated = true;
                break;
            }
        }
        if (!allocated) {
            cout << "Process " << i + 1 << " of size " << processSizes[i] 
                 << "KB could not be allocated (partition too small or no free partition).\n";
        }
    }

    // Calculate external fragmentation
    for (int j = 0; j < numPartitions; j++) {
        if (allocations[j] == -1) {
            externalFragmentation += partitionSize;
        }
    }
    cout << "Total External Fragmentation: " << externalFragmentation << "KB\n";
}

int main() {
    // Input for MVT
    int totalMemoryMVT = 1000; // Total memory in KB
    vector<int> processSizesMVT = {200, 300, 400, 500}; // Process sizes in KB

    // Simulate MVT
    simulateMVT(totalMemoryMVT, processSizesMVT);

    // Input for MFT
    int totalMemoryMFT = 1000; // Total memory in KB
    int partitionSize = 300;   // Fixed partition size in KB
    vector<int> processSizesMFT = {200, 300, 400, 150}; // Process sizes in KB

    // Simulate MFT
    simulateMFT(totalMemoryMFT, partitionSize, processSizesMFT);

    return 0;
}
