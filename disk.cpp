#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const int DISK_SIZE = 200; // Number of tracks
const int INITIAL_POSITION = 50; // Starting position of disk arm

// Function to calculate seek time and print sequence for a given algorithm
int calculateSeekTime(const vector<int> &sequence, int start) {
    int totalSeekTime = 0;
    int currentPosition = start;

    cout << "Access sequence: ";
    for (int track : sequence) {
        cout << track << " ";
        totalSeekTime += abs(track - currentPosition);
        currentPosition = track;
    }

    cout << "\nTotal Seek Time: " << totalSeekTime << " tracks\n";
    return totalSeekTime;
}

// FCFS Disk Scheduling Algorithm
void FCFS(vector<int> requestQueue, int start) {
    cout << "\nFCFS Disk Scheduling:\n";
    calculateSeekTime(requestQueue, start);
}

// SCAN (Elevator) Disk Scheduling Algorithm
void SCAN(vector<int> requestQueue, int start) {
    cout << "\nSCAN Disk Scheduling:\n";

    requestQueue.push_back(start);
    sort(requestQueue.begin(), requestQueue.end());
    auto pos = find(requestQueue.begin(), requestQueue.end(), start);
    vector<int> sequence;

    // Moving towards the higher tracks first
    for (auto it = pos; it != requestQueue.end(); ++it)
        sequence.push_back(*it);

    // Moving back to the start
    for (auto it = pos - 1; it >= requestQueue.begin(); --it)
        sequence.push_back(*it);

    calculateSeekTime(sequence, start);
}

// C-SCAN Disk Scheduling Algorithm
void C_SCAN(vector<int> requestQueue, int start) {
    cout << "\nC-SCAN Disk Scheduling:\n";

    requestQueue.push_back(start);
    sort(requestQueue.begin(), requestQueue.end());
    auto pos = find(requestQueue.begin(), requestQueue.end(), start);
    vector<int> sequence;

    // Moving towards the higher end
    for (auto it = pos; it != requestQueue.end(); ++it)
        sequence.push_back(*it);

    // Jump to the start and go up again
    for (auto it = requestQueue.begin(); it != pos; ++it)
        sequence.push_back(*it);

    calculateSeekTime(sequence, start);
}

// LOOK Disk Scheduling Algorithm
void LOOK(vector<int> requestQueue, int start) {
    cout << "\nLOOK Disk Scheduling:\n";

    requestQueue.push_back(start);
    sort(requestQueue.begin(), requestQueue.end());
    auto pos = find(requestQueue.begin(), requestQueue.end(), start);
    vector<int> sequence;

    // Move towards the higher tracks
    for (auto it = pos; it != requestQueue.end(); ++it)
        sequence.push_back(*it);

    // Reverse direction and go down
    for (auto it = pos - 1; it >= requestQueue.begin(); --it)
        sequence.push_back(*it);

    calculateSeekTime(sequence, start);
}

// C-LOOK Disk Scheduling Algorithm
void C_LOOK(vector<int> requestQueue, int start) {
    cout << "\nC-LOOK Disk Scheduling:\n";

    requestQueue.push_back(start);
    sort(requestQueue.begin(), requestQueue.end());
    auto pos = find(requestQueue.begin(), requestQueue.end(), start);
    vector<int> sequence;

    // Move up towards the end
    for (auto it = pos; it != requestQueue.end(); ++it)
        sequence.push_back(*it);

    // Jump to the lowest pending request and go up again
    for (auto it = requestQueue.begin(); it != pos; ++it)
        sequence.push_back(*it);

    calculateSeekTime(sequence, start);
}

// Main function to run all algorithms and compare results
int main() {
    vector<int> requestQueue = {98, 183, 37, 122, 14, 124, 65, 67};

    cout << "Initial Disk Position: " << INITIAL_POSITION << "\nRequest Queue: ";
    for (int track : requestQueue) 
        cout << track << " ";

    cout << "\n\n";

    int fcfsSeekTime = calculateSeekTime(requestQueue, INITIAL_POSITION);
    FCFS(requestQueue, INITIAL_POSITION);

    int scanSeekTime = calculateSeekTime(requestQueue, INITIAL_POSITION);
    SCAN(requestQueue, INITIAL_POSITION);

    int cscanSeekTime = calculateSeekTime(requestQueue, INITIAL_POSITION);
    C_SCAN(requestQueue, INITIAL_POSITION);

    int lookSeekTime = calculateSeekTime(requestQueue, INITIAL_POSITION);
    LOOK(requestQueue, INITIAL_POSITION);

    int clookSeekTime = calculateSeekTime(requestQueue, INITIAL_POSITION);
    C_LOOK(requestQueue, INITIAL_POSITION);

    // Display comparison in tabular format
    cout << "\n\nAlgorithm Comparison:\n";
    cout << setw(10) << "Algorithm" << setw(15) << "Seek Time\n";
    cout << "---------------------------------\n";
    cout << setw(10) << "FCFS" << setw(15) << fcfsSeekTime << "\n";
    cout << setw(10) << "SCAN" << setw(15) << scanSeekTime << "\n";
    cout << setw(10) << "C-SCAN" << setw(15) << cscanSeekTime << "\n";
    cout << setw(10) << "LOOK" << setw(15) << lookSeekTime << "\n";
    cout << setw(10) << "C-LOOK" << setw(15) << clookSeekTime << "\n";

    return 0;
}
