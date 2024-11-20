#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    string processID; // Added to match second structure (optional depending on your use case)
};

// Comparison function for sorting processes
bool compare(const Process &a, const Process &b) {
    if (a.remainingTime != b.remainingTime)  
        return a.remainingTime < b.remainingTime;
    if (a.arrivalTime != b.arrivalTime)
        return a.arrivalTime < b.arrivalTime;
    return a.id < b.id;
}

int main() {
    int n;
    cout << "Enter the total number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << " Arrival time: ";
        cin >> processes[i].arrivalTime;
        cout << "Process " << i + 1 << " Burst time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    int timeQuantum;
    cout << "Enter the value of time QUANTUM: ";
    cin >> timeQuantum;

    int time = 0, remain = n, wt = 0, tat = 0, completed = 0;
    int prev = -1;
    double totalWaitingTime = 0, totalTurnAroundTime = 0;

    cout << "\nProcess\t\t: Turnaround Time : Waiting Time\n\n";

    while (remain != 0) {
        // Sort processes based on remaining time, arrival time, and process ID
        sort(processes.begin(), processes.end(), compare);

        bool processExecuted = false;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime <= timeQuantum) {
                    time += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    remain--;
                    processes[i].turnaroundTime = time - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

                    totalWaitingTime += processes[i].waitingTime;
                    totalTurnAroundTime += processes[i].turnaroundTime;

                    cout << "Process[" << processes[i].id << "]\t: " 
                         << processes[i].turnaroundTime << "\t: " 
                         << processes[i].waitingTime << endl;
                } else {
                    processes[i].remainingTime -= timeQuantum;
                    time += timeQuantum;
                }
                processExecuted = true;
                break;
            }
        }

        if (!processExecuted) {
            time++;
        }
    }

    cout << "Average waiting time: " << totalWaitingTime / n << endl;
    cout << "Average turnaround time: " << totalTurnAroundTime / n << endl;

    return 0;
}
