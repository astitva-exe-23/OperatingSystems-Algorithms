#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int LRU(const vector<int>& referenceString,int frameCount){
    unordered_map<int,int>frames;
    int pagefaults=0;

    for(int i=0;i<referenceString.size();i++){
        int page = referenceString[i];
        if(frames.find(page)==frames.end()){
            if(frames.size()<frameCount){
                frames[page]=i;
            }
            else{
                int lruPage=-1,lruTime=i;
                for(auto &entry:frames){
                    if(entry.second<lruTime){
                        lruTime=entry.second;
                        lruPage=entry.first;
                    }
                }
                frames.erase(lruPage);
                frames[page]=i;
            }
            pagefaults++;
        }
        else{
            frames[page]=i;
        }
    }
    return pagefaults;
}