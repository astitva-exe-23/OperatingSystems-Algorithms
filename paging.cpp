#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

const int PAGE_SIZE = 4096;  // 4KB page size
const int PHYSICAL_MEMORY_SIZE = 1 << 30;  // 1GB physical memory
const int OFFSET_BITS = 12;  // Offset of 12 bits (log2(PAGE_SIZE))
const int NUM_FRAMES = PHYSICAL_MEMORY_SIZE / PAGE_SIZE;  // Total frames

// Page Table Entry structure
struct PageTableEntry {
    int frameNumber;  // Frame number in physical memory
    bool isValid;     // Valid bit to check if the page is in memory
};

// Simulate the page table and frame counter
unordered_map<int, PageTableEntry> pageTable;
int frameCounter = 0;  // Tracks the next available frame

/**
 * Handles a page fault by assigning a new frame to the page.
 * 
 * @param pageNumber - The logical page number causing the fault
 * @return The frame number assigned to the page
 */
int handlePageFault(int pageNumber) {
    cout << "Page fault occurred for page: " << pageNumber << endl;

    // Check if there's available physical memory
    if (frameCounter >= NUM_FRAMES) {
        cerr << "Error: Out of physical memory!" << endl;
        exit(1);
    }

    // Assign a new frame to the page
    pageTable[pageNumber] = {frameCounter, true};
    return frameCounter++;
}

/**
 * Translates a logical address to a physical address.
 * 
 * @param logicalAddress - The logical address to translate
 */
void translateAddress(uint32_t logicalAddress) {
    // Extract page number and offset from the logical address
    int offset = logicalAddress & ((1 << OFFSET_BITS) - 1);
    int pageNumber = logicalAddress >> OFFSET_BITS;

    cout << "\nLogical Address: 0x" << hex << setw(8) << setfill('0') << logicalAddress << dec << endl;
    cout << "Page Number: " << pageNumber << ", Offset: " << offset << endl;

    // Check if the page is in the page table
    if (pageTable.find(pageNumber) == pageTable.end() || !pageTable[pageNumber].isValid) {
        handlePageFault(pageNumber);
    }

    // Get the frame number from the page table
    int frameNumber = pageTable[pageNumber].frameNumber;

    // Compute the physical address
    int physicalAddress = (frameNumber << OFFSET_BITS) | offset;

    cout << "Physical Address: 0x" << hex << physicalAddress << dec
         << " (Frame: " << frameNumber << ", Offset: " << offset << ")\n";
}

/**
 * Main function to test the single-level paging simulation.
 */
int main() {
    vector<uint32_t> testAddresses = {0x12345678, 0xABCDEF12, 0x98765432};

    // Translate test addresses
    for (uint32_t address : testAddresses) {
        translateAddress(address);
    }

    // Allow the user to enter additional logical addresses
    while (true) {
        string userInput;
        cout << "\nEnter a logical address in hexadecimal (or 'exit' to quit): ";
        cin >> userInput;

        if (userInput == "exit") break;

        uint32_t logicalAddress;
        stringstream ss;
        ss << hex << userInput;
        ss >> logicalAddress;

        translateAddress(logicalAddress);
    }

    return 0;
}
