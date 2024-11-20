#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

int Optimal(const vector<int>& referenceString, int frameCount) {
    unordered_map<int, bool> frames;
    int pageFaults = 0;

    for (int i = 0; i < referenceString.size(); i++) {
        int page = referenceString[i];
        if (frames.find(page) == frames.end()) {
            if (frames.size() < frameCount) {
                frames[page] = true;
            } else {
                int farthestPage = -1, farthestIndex = -1;
                for (auto& entry : frames) {
                    int nextUse = -1;
                    for (int j = i + 1; j < referenceString.size(); j++) {
                        if (referenceString[j] == entry.first) {
                            nextUse = j;
                            break;
                        }
                    }

                    if (nextUse == -1) {
                        farthestPage = entry.first;
                        break;
                    }
                    if (nextUse > farthestIndex) {
                        farthestIndex = nextUse;
                        farthestPage = entry.first;
                    }
                }
                frames.erase(farthestPage);
                frames[page] = true;
            }
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

    int pageFaults = Optimal(referenceString, frameCount);
    cout << "Optimal Page Faults: " << pageFaults << endl;

    return 0;
}
