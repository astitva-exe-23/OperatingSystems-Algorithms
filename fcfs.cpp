#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>

using namespace std;

struct Process{
    string Process_id;
    int arrivaltime;
    int bursttime;
    int completiontime;
    int waitingtime;
    int turnaroundtime;
};

void inputProcesses(vector<Process> &processes,int &numprocesses){
    cout<<"Enter Number Of processes";
    cin>>numprocesses;

    for(int i=0;i<numprocesses;i++){
        Process p;
        cin>>p.Process_id;
        cin>>p.arrivaltime;
        cin>>p.bursttime;
        processes.push_back(p);
    }
}

void fcfs(vector<Process> &processes){
    sort(processes.begin(),processes.end(),[](Process &a,Process &b){
        return a.arrivaltime<b.arrivaltime;
    });
    int currentTime=0;
    for(auto &p:processes){
        if(currentTime <p.arrivaltime){
            if(currentTime<p.arrivaltime){
                currentTime=p.arrivaltime;
            }
            p.waitingtime=currentTime-p.arrivaltime;
            p.completiontime=currentTime+p.bursttime;
            p.turnaroundtime = p.completiontime-p.arrivaltime;
            currentTime+=p.bursttime;
        }
    }
}

void calculateMetrics(const vector<Process> &processes){
    double totalWT=0;
    double totalTat=0;

    for(const auto &p:processes){
        totalTat+=p.turnaroundtime;
        totalWT+=p.waitingtime;
        
    }
}
