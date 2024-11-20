#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Process{
    string processId;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

bool compareByArrival(Process a, Process b){
    return a.arrivalTime<b.arrivalTime;
}

bool compareByBurst(Process a,Process b){
    return a.burstTime<b.burstTime;
}

int main(){
    int n;
    cin>>n;

    vector<Process>processes(n);

    for(int i=0;i<n;i++){
        cin>>processes[i].processId>>processes[i].arrivalTime>>processes[i].burstTime;
        processes[i].waitingTime=0;
        processes[i].turnaroundTime=0;
    }

    sort(processes.begin(),processes.end(), compareByArrival);
    int completionTime=0;
    int completed=0;
    double totalWaiting=0;
    double totalTurnaround=0;

    while(completed<n){
        vector<Process>readyQueue;
        for(int i=0;i<n;i++){
            if(processes[i].arrivalTime<=completionTime && processes[i].burstTime>0){
                readyQueue.push_back(processes[i]);
            }
        }
        if(readyQueue.empty()){
            completionTime++;
            continue;
        }
        sort(readyQueue.begin(),readyQueue.end(),compareByBurst);
        Process &currentProcess = readyQueue[0];

        for(int i=0;i<n;i++){
            if(processes[i].processId==currentProcess.processId){
                processes[i].waitingTime = completionTime-processes[i].arrivalTime;
                completionTime+=processes[i].burstTime;
                processes[i].turnaroundTime=completionTime-processes[i].arrivalTime;
                totalWaiting+=processes[i].waitingTime;
                totalTurnaround+=processes[i].turnaroundTime;
                processes[i].burstTime=0;
                completed++;
                break;
            }
        }
    }
}