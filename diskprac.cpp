#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<iomanip>
using namespace std;


const int DISK_SIZE=200;
const int INITIAL_POSITION=50;

int calculateSeektime(const vector<int> &sequence,int start){
    int totalSeekTime=0;
    int currentposition=start;

    cout<<"Access Sequence";
    for(int track:sequence){
        cout<<track<<" ";
        totalSeekTime+=abs(track-currentposition);
        currentposition=track;
    }

    cout<<"\n total seek time:"<<totalSeekTime<<"tracks\n";
    return totalSeekTime;
}

void FCFS(vector<int> requestQueue, int start) {
    cout << "\nFCFS Disk Scheduling:\n";
    calculateSeektime(requestQueue, start);
}

void SCAN(vector<int> requestQueue, int start){
    cout<<"\n SCAN DISK SCHEDULING:\n";
    requestQueue.push_back(start);
    sort(requestQueue.begin(),requestQueue.end());
    auto pos = find(requestQueue.begin(),requestQueue.end(),start);
    vector<int>sequence;

    //higher tracks
    for(auto it=pos;it!=requestQueue.end();it++){
        sequence.push_back(*it);
    }
//lower tracks
    for(auto it=pos-1;it>=requestQueue.begin();it--){
        sequence.push_back(*it);
    }

    calculateSeektime(sequence,start);
}


void LOOK(vector<int>requestQueue,int start){
    requestQueue.push_back(start);
    sort(requestQueue.begin(),requestQueue.end());
    auto pos = find(requestQueue.begin(),requestQueue.end(),start);
    vector<int> sequence;

    //higher tracks
    
}