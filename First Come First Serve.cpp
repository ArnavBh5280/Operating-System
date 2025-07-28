#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Define INT_MAX manually
#define INT_MAX 2147483647

struct Process {
    int id, arrivalTime, burstTime, priority, startTime, completionTime, turnAroundTime, waitingTime;
};

// FCFS Scheduling
void FCFS(vector<Process> &processes) {
    int time = 0;
    for (auto &p : processes) {
        if (time < p.arrivalTime) time = p.arrivalTime;
        p.startTime = time;
        p.completionTime = time + p.burstTime;
        p.turnAroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnAroundTime - p.burstTime;
        time += p.burstTime;
    }

    cout << "\nFCFS Scheduling:\n";
    for (const auto &p : processes) {
        cout << "Process " << p.id << ": Start Time = " << p.startTime 
             << ", Completion Time = " << p.completionTime 
             << ", Turn Around Time = " << p.turnAroundTime 
             << ", Waiting Time = " << p.waitingTime << "\n";
    }
}

// SJF Scheduling
void SJF(vector<Process> &processes) {
    int time = 0, completed = 0, n = processes.size();
    vector<bool> visited(n, false);

    cout << "\nSJF Scheduling:\n";
    while (completed < n) {
        int idx = -1, minBurstTime = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i].arrivalTime <= time && processes[i].burstTime < minBurstTime) {
                idx = i;
                minBurstTime = processes[i].burstTime;
            }
        }

        if (idx == -1) { 
            time++;
            continue;
        }

        visited[idx] = true;
        processes[idx].startTime = time;
        processes[idx].completionTime = time + processes[idx].burstTime;
        processes[idx].turnAroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;
        time += processes[idx].burstTime;
        completed++;

        cout << "Process " << processes[idx].id << ": Start Time = " << processes[idx].startTime 
             << ", Completion Time = " << processes[idx].completionTime 
             << ", Turn Around Time = " << processes[idx].turnAroundTime 
             << ", Waiting Time = " << processes[idx].waitingTime << "\n";
    }
}

// Priority Scheduling
void PriorityScheduling(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.priority < b.priority;
    });
    FCFS(processes);  // Reuse FCFS logic
}

// Round Robin Scheduling
void RoundRobin(vector<Process> &processes, int timeQuantum) {
    queue<Process> readyQueue;
    vector<int> remainingBurstTime(processes.size());
    int time = 0, completed = 0;

    for (size_t i = 0; i < processes.size(); i++) {
        remainingBurstTime[i] = processes[i].burstTime;
    }

    cout << "\nRound Robin Scheduling (Time Quantum = " << timeQuantum << "):\n";
    while (completed < processes.size()) {
        for (size_t i = 0; i < processes.size(); i++) {
            if (remainingBurstTime[i] > 0 && processes[i].arrivalTime <= time) {
                if (remainingBurstTime[i] <= timeQuantum) {
                    time += remainingBurstTime[i];
                    remainingBurstTime[i] = 0;
                    completed++;
                    processes[i].completionTime = time;
                    processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
                } else {
                    time += timeQuantum;
                    remainingBurstTime[i] -= timeQuantum;
                }
                cout << "Process " << processes[i].id << ": Remaining Burst Time = " << remainingBurstTime[i] << "\n";
            }
        }
    }

    for (const auto &p : processes) {
        cout << "Process " << p.id << ": Completion Time = " << p.completionTime 
             << ", Turn Around Time = " << p.turnAroundTime 
             << ", Waiting Time = " << p.waitingTime << "\n";
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 5, 2}, {2, 1, 3, 1}, {3, 2, 8, 3}, {4, 3, 6, 2}
    };

    cout << "Process details:\n";
    for (const auto &p : processes) {
        cout << "Process " << p.id << ": Arrival Time = " << p.arrivalTime 
             << ", Burst Time = " << p.burstTime 
             << ", Priority = " << p.priority << "\n";
    }

    FCFS(processes);

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });
    SJF(processes);

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });
    PriorityScheduling(processes);

    int timeQuantum = 3;
    RoundRobin(processes, timeQuantum);

    return 0;
}
