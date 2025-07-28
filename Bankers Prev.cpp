#include <iostream>
#include <vector>
using namespace std;

// Function to check if the system is in a safe state
bool isSafe(vector<vector<int>> &allocation, vector<vector<int>> &need, vector<int> &available, int numProcesses, int numResources) {
    vector<bool> finish(numProcesses, false);
    vector<int> work = available;
    vector<int> safeSequence;

    int count = 0;
    while (count < numProcesses) {
        bool found = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < numResources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence.push_back(i);
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            return false; // System is not in a safe state
        }
    }

    cout << "System is in a safe state.\nSafe Sequence: ";
    for (int i = 0; i < safeSequence.size(); i++) {
        cout << "P" << safeSequence[i];
        if (i < safeSequence.size() - 1) cout << " -> ";
    }
    cout << "\n";
    return true;
}

// Function to request resources for a process
bool requestResources(vector<vector<int>> &allocation, vector<vector<int>> &need, vector<int> &available, int processID, vector<int> &request, int numResources) {
    // Check if the request is less than or equal to need
    for (int j = 0; j < numResources; j++) {
        if (request[j] > need[processID][j]) {
            cout << "Error: Process has exceeded its maximum claim.\n";
            return false;
        }
    }

    // Check if the request is less than or equal to available
    for (int j = 0; j < numResources; j++) {
        if (request[j] > available[j]) {
            cout << "Resources are not available.\n";
            return false;
        }
    }

    // Pretend to allocate the resources
    for (int j = 0; j < numResources; j++) {
        available[j] -= request[j];
        allocation[processID][j] += request[j];
        need[processID][j] -= request[j];
    }

    // Check if the system remains in a safe state
    if (isSafe(allocation, need, available, allocation.size(), numResources)) {
        cout << "Request granted.\n";
        return true;
    } else {
        // Rollback the changes if unsafe
        for (int j = 0; j < numResources; j++) {
            available[j] += request[j];
            allocation[processID][j] -= request[j];
            need[processID][j] += request[j];
        }
        cout << "Request denied to prevent unsafe state.\n";
        return false;
    }
}

int main() {
    int numProcesses, numResources;

    // Input number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the number of resources: ";
    cin >> numResources;

    vector<vector<int>> maximum(numProcesses, vector<int>(numResources));
    vector<vector<int>> allocation(numProcesses, vector<int>(numResources));
    vector<vector<int>> need(numProcesses, vector<int>(numResources));
    vector<int> available(numResources);

    // Input Maximum Matrix
    cout << "\nEnter the Maximum Resource Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> maximum[i][j];
        }
    }

    // Input Allocation Matrix
    cout << "\nEnter the Allocation Resource Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> allocation[i][j];
        }
    }

    // Input Available Resources
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

    // Output Need Matrix
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cout << need[i][j] << " ";
        }
        cout << "\n";
    }

    // Request resources for a process
    char choice;
    do {
        int processID;
        vector<int> request(numResources);

        cout << "\nEnter the Process ID (0 to " << numProcesses - 1 << "): ";
        cin >> processID;

        cout << "Enter the resource request for process P" << processID << ":\n";
        for (int j = 0; j < numResources; j++) {
            cin >> request[j];
        }

        // Process the resource request
        requestResources(allocation, need, available, processID, request, numResources);

        cout << "\nDo you want to make another request? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
