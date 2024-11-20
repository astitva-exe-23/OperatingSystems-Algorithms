#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int FIFO(const vector<int>& referenceString, int frameCount) {
    unordered_map<int, bool> frames;
    queue<int> frameQueue;
    int pageFaults = 0;

    for (int page : referenceString) {
        if (frames.find(page) == frames.end()) {
            if (frameQueue.size() < frameCount) {
                frameQueue.push(page);
            } else {
                int removedPage = frameQueue.front();
                frameQueue.pop();
                frames.erase(removedPage);
                frameQueue.push(page);
            }
            frames[page] = true;
            pageFaults++;
        }
    }

    return pageFaults;
}

int main() {
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3}; // Example reference string
    int frameCount;

    cout << "Enter the number of frames: ";
    cin >> frameCount;

    int pageFaults = FIFO(referenceString, frameCount);
    cout << "FIFO Page Faults: " << pageFaults << endl;

    return 0;
}
