#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>


using namespace std;

struct Process{
    int id;
    int arrivalTime;
    int bursttime;
    int remaintime;
    int waittime;
    int turnaroundtime;
};

//comparison function for sorting processes
bool compare(const Process &a, const Process &b){
    if(a.remaintime!=b.remaintime){
        return a.remaintime<b.remaintime;
    }
    if(a.arrivalTime!=b.arrivalTime){
        return a.arrivalTime<b.arrivalTime;
    }
    return a.id<b.id;
}

int main(){
    int n;
    cin>>n;

    vector<Process>processes(n);

    for(int i=0;i<n;i++){
        processes[i].id=i+1;
        cout<<"Process"<<i+1;
        cin>>processes[i].arrivalTime;
        cin>>processes[i].bursttime;
        processes[i].remaintime=processes[i].bursttime;
        processes[i].waittime=0;
        processes[i].turnaroundtime=0;
    }

    int timeQuantum;
    cout<<"Enter the value of time quantum:";
    cin>>timeQuantum;

    int time=0,remain=n,wt=0,tat=0,completed=0;
    int prev=-1;

    double totalWaitingTime=0;
    double totalTat=0;

    while(remain!=0){
        sort(processes.begin(),processes.end(),compare);

        bool processExecuted=false;
        for(int i =0;i<n;i++){
            if(processes[i].arrivalTime<=time && processes[i].remaintime>0){
                if(processes[i].remaintime<=timeQuantum){
                    time+=processes[i].remaintime;
                    processes[i].remaintime=0;
                    remain--;
                    processes[i].turnaroundtime = time-processes[i].arrivalTime;
                    processes[i].waittime=processes[i].turnaroundtime-processes[i].bursttime;

                    totalWaitingTime+=processes[i].waittime;
                    totalTat+=processes[i].turnaroundtime;
                    
                    cout<<"Processes["<<processes[i].id<<"]\t"
                    <<processes[i].turnaroundtime<<processes[i].waittime<<endl;
                }
                else{
                    processes[i].remaintime-=timeQuantum;
                    time+=timeQuantum;
                }
                processExecuted=true;
                break;
            }
        }
        if(!processExecuted){
            time++;
        }
    }
    cout<<"Avg Wait time"<<totalWaitingTime<<endl;
    cout<<"Av turntime"<<totalTat<<endl;
    return 0;

}