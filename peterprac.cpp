#include<iostream>
#include<thread>
#include<atomic>
#include<chrono>
using namespace std;

atomic<bool> flag[2] = {false,false};
atomic<int> turn(0);


void critical_section(int thread_id){
    cout<<"Thread"<<thread_id<<"is in the critical section"<<endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout<<"Thread"<<thread_id<<"is leaving the critical section"<<endl;
}

void thread_0(){
    for(int i = 0;i<5;i++){
        flag[0] = true;
        turn =1;
        while(flag[1] && turn ==1);

        critical_section(0);

        flag[0]=false;

        this_thread::sleep_for(chrono::seconds(1));
    }
}

void thread_1(){
    for(int i = 0;i<5;i++){
        flag[1] = true;
        turn =0;
        while(flag[0] && turn ==0);

        critical_section(1);

        flag[1]=false;

        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main(){
    thread t0(thread_0);
    thread t1(thread_1);
    t0.join();
    t1.join();

    return 0;
}