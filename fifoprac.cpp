#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;

int FIFO(const vector<int>& referenceString,int frameConut){
    unordered_map<int,bool>frames;
    queue<int>frameQueue;
    int pageFaults=0;

    for(int page:referenceString){
        if(frames.find(page)==frames.end()){
            if(frameQueue.size()<frameConut){
                frameQueue.push(page);
            }
            else{
                int removedPage=frameQueue.front();
                frameQueue.pop();
                frames.erase(removedPage);
                frameQueue.push(page);
            }
            frames[page]=true;
            pagefaults++;
        }
    }
    return pagefaults;
}