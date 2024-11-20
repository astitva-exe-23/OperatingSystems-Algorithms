#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

struct Process{
    string processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundtime;
};

int main(){
    int n;
    cout<<"Enter the number of process";
    vector<Process>processes(n);

    for(int i=0;i<n;i++){
        cin>>processes[i].processID>>processes[i].arrivalTime>>processes[i].burstTime;
        processes[i].remainingTime=processes[i].burstTime;
        processes[i].waitingTime=0;
        processes[i].turnaroundtime=0;
    }

    int currentTime=0;
    int completed=0;
    double totalWaitingTime=0;
    double totalTurnAroundTime=0;
    int prev=-1;

    while(completed!=n){
        int minTime=INT_MAX;
        int shortest=-1;

        for(int i=0;i<n;i++){
            if(processes[i].arrivalTime<=currentTime && processes[i].remainingTime<minTime && processes[i].remainingTime>0){
                minTime=processes[i].remainingTime;
                shortest=i;
            }
        }
        if(shortest==-1){
            currentTime++;
            continue;
        }
        if(prev!=shortest){
            if(prev!=-1){
                cout<<"processes"<<processes[prev].processID<<"preempted at time"<<currentTime<<endl;
            }
            cout<<"Processes"<<processes[shortest].processID<<"started execution at time"<<currentTime<<endl;
            prev=shortest;
        }
        processes[shortest].remainingTime--; //execution
        currentTime++;

        processes[shortest].remainingTime--;
        currentTime++;

        if(processes[shortest].remainingTime==0){
            completed++;
            processes[shortest].turnaroundtime=currentTime-processes[shortest].arrivalTime;
            processes[shortest].waitingTime = processes[shortest].turnaroundtime-processes[shortest].burstTime;

            totalWaitingTime += processes[shortest].waitingTime;
            totalTurnAroundTime +=processes[shortest].turnaroundtime;
        }
    }

}