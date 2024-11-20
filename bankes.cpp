#include <iostream>
#include <vector>
using namespace std;

// Function to check if the system is in a safe state
bool isSafe(vector<vector<int>> &max, vector<vector<int>> &allocation,
            vector<vector<int>> &need, vector<int> &available, int processes, int resources) {
    vector<int> work = available;
    vector<bool> finish(processes, false);
    vector<int> safeSequence;

    for (int count = 0; count < processes; ++count) {
        bool found = false;
        for (int p = 0; p < processes; ++p) {
            if (!finish[p]) {
                bool canProceed = true;
                for (int r = 0; r < resources; ++r) {
                    if (need[p][r] > work[r]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (int r = 0; r < resources; ++r) {
                        work[r] += allocation[p][r];
                    }
                    safeSequence.push_back(p);
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; // System is not in a safe state
        }
    }

    cout << "Safe sequence: ";
    for (int i = 0; i < safeSequence.size(); ++i) {
        cout << safeSequence[i] << " ";
    }
    cout << endl;
    return true;
}

// Function to request resources for a process
bool requestResources(vector<vector<int>> &max, vector<vector<int>> &allocation,
                      vector<vector<int>> &need, vector<int> &available, int processes,
                      int resources, int processNum, vector<int> request) {
    // Check if request exceeds need
    for (int r = 0; r < resources; ++r) {
        if (request[r] > need[processNum][r]) {
            cout << "Error: Process " << processNum << " has exceeded its maximum claim." << endl;
            return false;
        }
        if (request[r] > available[r]) {
            cout << "Resources unavailable for process " << processNum << endl;
            return false;
        }
    }

    // Pretend to allocate resources
    for (int r = 0; r < resources; ++r) {
        available[r] -= request[r];
        allocation[processNum][r] += request[r];
        need[processNum][r] -= request[r];
    }

    // Check if the system is in a safe state
    if (isSafe(max, allocation, need, available, processes, resources)) {
        cout << "Request granted to process " << processNum << endl;
        return true;
    } else {
        // Revert allocation if unsafe
        for (int r = 0; r < resources; ++r) {
            available[r] += request[r];
            allocation[processNum][r] -= request[r];
            need[processNum][r] += request[r];
        }
        cout << "Request denied. The system would be unsafe." << endl;
        return false;
    }
}

int main() {
    int processes, resources;
    cout << "Enter the number of processes: ";
    cin >> processes;
    cout << "Enter the number of resource types: ";
    cin >> resources;

    vector<vector<int>> max(processes, vector<int>(resources));
    vector<vector<int>> allocation(processes, vector<int>(resources));
    vector<vector<int>> need(processes, vector<int>(resources));
    vector<int> available(resources);

    // Input max matrix
    cout << "Enter the Max matrix (maximum demand for each process):" << endl;
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            cin >> max[i][j];
        }
    }

    // Input allocation matrix
    cout << "Enter the Allocation matrix (currently allocated resources for each process):" << endl;
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            cin >> allocation[i][j];
            // Calculate the need matrix as Max - Allocation
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Input available resources
    cout << "Enter the available resources (instances of each resource type):" << endl;
    for (int i = 0; i < resources; ++i) {
        cin >> available[i];
    }

    // Simulate resource requests
    char cont = 'y';
    while (cont == 'y' || cont == 'Y') {
        int processNum;
        vector<int> request(resources);
        cout << "Enter the process number making a request: ";
        cin >> processNum;
        cout << "Enter the request for resources (instances of each resource type):" << endl;
        for (int r = 0; r < resources; ++r) {
            cin >> request[r];
        }

        if (!requestResources(max, allocation, need, available, processes, resources, processNum, request)) {
            cout << "Request could not be granted." << endl;
        }

        cout << "Do you want to make another request? (y/n): ";
        cin >> cont;
    }

    return 0;
}
