#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
int main()
{
const int no_of_philosophers=20;
struct Chopstics
{
public :
 Chopstics(){;}
  mutex mu;
};
auto eat=[](Chopstics &left_chopstics,Chopstics& right_chopstics,int philosopher_number){
unique_lock<mutex> llock(left_chopstics.mu);
unique_lock<mutex> rlock(right_chopstics.mu);
cout<<"Philosopher "<<philosopher_number<<" is eating"<<endl;
this_thread::sleep_for(chrono::milliseconds(1500));
cout<<"Philosopher "<<philosopher_number<< " has finished eating "<<endl;
};
Chopstics chp[no_of_philosophers];
thread philosopher[no_of_philosophers];
cout<<"Philosopher "<<(0+1)<<" is reading.. "<<endl;
philosopher[0]=thread(eat,ref(chp[0]),ref(chp[no_of_philosophers-1]),(0+1));
for(int i=1;i<no_of_philosophers;++i)
{
 cout<<"Philosopher "<<(i+1)<<" is reading.."<<endl;
 philosopher[i]=thread(eat,ref(chp[i]),ref(chp[i-1]),(i+1));
}
for(auto &ph:philosopher){
 ph.join();
}
return 0;
}