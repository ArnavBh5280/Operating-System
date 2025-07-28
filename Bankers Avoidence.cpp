#include <iostream>
#include <vector>
using namespace std;

// Function to check if the system is in a safe state
bool isSafe(vector<vector<int>> &allocation, vector<vector<int>> &need, vector<int> &available, int numProcesses, int numResources) {
    vector<bool> finish(numProcesses, false); // To track finished processes
    vector<int> safeSequence(numProcesses);  // To store the safe sequence
    vector<int> work = available;            // Work vector initialized to available resources

    int count = 0; // To track the number of processes finished
    while (count < numProcesses) {
        bool found = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) { // If the process is not finished
                bool canAllocate = true;
                for (int j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) { // If the process's need exceeds available resources
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) { // If the process can be allocated
                    for (int j = 0; j < numResources; j++) {
                        work[j] += allocation[i][j]; // Add allocated resources back to work
                    }
                    safeSequence[count++] = i;
                    finish[i] = true; // Mark the process as finished
                    found = true;
                }
            }
        }

        if (!found) { // If no process can be allocated, the system is not safe
            cout << "System is NOT in a safe state.\n";
            return false;
        }
    }

    // Print the safe sequence
    cout << "System is in a safe state.\nSafe Sequence: ";
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << safeSequence[i];
        if (i < numProcesses - 1) cout << " -> ";
    }
    cout << "\n";
    return true;
}

int main() {
    // Input parameters
    int numProcesses, numResources;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the number of resources: ";
    cin >> numResources;

    vector<vector<int>> maximum(numProcesses, vector<int>(numResources));
    vector<vector<int>> allocation(numProcesses, vector<int>(numResources));
    vector<vector<int>> need(numProcesses, vector<int>(numResources));
    vector<int> available(numResources);

    // Input the Maximum Matrix
    cout << "\nEnter the Maximum Resource Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> maximum[i][j];
        }
    }

    // Input the Allocation Matrix
    cout << "\nEnter the Allocation Resource Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> allocation[i][j];
        }
    }

    // Input the Available Resources
    cout << "\nEnter the Available Resources:\n";
    for (int i = 0; i < numResources; i++) {
        cin >> available[i];
    }

    // Calculate the Need Matrix
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    // Output the Need Matrix
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cout << need[i][j] << " ";
        }
        cout << "\n";
    }

    // Check if the system is in a safe state
    isSafe(allocation, need, available, numProcesses, numResources);

    return 0;
}

