#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;

// Shared variables for Peterson's algorithm
atomic<bool> flag[2] = {false, false}; // Flag for each thread
atomic<int> turn(0);                  // Whose turn is it to enter the critical section

// Critical section function
void critical_section(int thread_id) {
    cout << "Thread " << thread_id << " is in the critical section" << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Simulate time in the critical section
    cout << "Thread " << thread_id << " is leaving the critical section" << endl;
}

// Function for thread 0
void thread_0() {
    for (int i = 0; i < 5; ++i) { // Run multiple times to demonstrate synchronization

        // Entry section for thread 0
        flag[0] = true;
        turn = 1;
        while (flag[1] && turn == 1); // Wait until it's safe to enter the critical section

        // Critical section
        critical_section(0);

        // Exit section for thread 0
        flag[0] = false;

        // Remainder section
        this_thread::sleep_for(chrono::seconds(1)); // Simulate time in the remainder section
    }
}

// Function for thread 1
void thread_1() {
    for (int i = 0; i < 5; ++i) { // Run multiple times to demonstrate synchronization

        // Entry section for thread 1
        flag[1] = true;
        turn = 0;
        while (flag[0] && turn == 0); // Wait until it's safe to enter the critical section

        // Critical section
        critical_section(1);

        // Exit section for thread 1
        flag[1] = false;

        // Remainder section
        this_thread::sleep_for(chrono::seconds(1)); // Simulate time in the remainder section
    }
}

// Main function to create and start threads
int main() {
    // Create two threads
    thread t0(thread_0);
    thread t1(thread_1);

    // Start the threads
    t0.join();
    t1.join();

    return 0;
}
