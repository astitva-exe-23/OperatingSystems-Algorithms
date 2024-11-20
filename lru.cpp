#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int LRU(const vector<int>& referenceString, int frameCount) {
    unordered_map<int, int> frames;
    int pageFaults = 0;

    for (int i = 0; i < referenceString.size(); i++) {
        int page = referenceString[i];
        if (frames.find(page) == frames.end()) {
            if (frames.size() < frameCount) {
                frames[page] = i;
            } else {
                int lruPage = -1, lruTime = i;
                for (auto& entry : frames) {
                    if (entry.second < lruTime) {
                        lruTime = entry.second;
                        lruPage = entry.first;
                    }
                }
                frames.erase(lruPage);
                frames[page] = i;
            }
            pageFaults++;
        } else {
            frames[page] = i;
        }
    }

    return pageFaults;
}

int main() {
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3}; // Example reference string
    int frameCount;

    cout << "Enter the number of frames: ";
    cin >> frameCount;

    int pageFaults = LRU(referenceString, frameCount);
    cout << "LRU Page Faults: " << pageFaults << endl;

    return 0;
}
