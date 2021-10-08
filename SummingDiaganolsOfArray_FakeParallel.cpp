// Online C++ compiler to run C++ program online
/*
Appears to be parallel bu this is still sequential



*/
#include <iostream>
#include <thread>
#include<vector>
#include<mutex>
#include<condition_variable>
using namespace std;
std::condition_variable condVar;
std::mutex mtx;
const int N=4;
// int a[N]={1,2,3,4,5,6,7,8,9,10};
int b[N][N]={
    {1,2,3,4},
    {1,2,3,4},
    {1,2,3,4},
    {1,2,3,4}
};
int count=0,sum=0;
int even=0, odd=0;

void print(bool isEven){
    unique_lock<mutex> lck(mtx);
    while(count<N){
    
        condVar.wait(lck,[&](){      return (count & 1)==isEven;  }   );
        if(count<N){
            if(count==(N-1-count))
                sum+=b[count][count];
            else
                sum+=(b[count][count]+b[count][N-1-count]);
            cout<<(count++)<<":"<<this_thread::get_id()<<"\n";
            // cout<<a[count++]++<<":"<<this_thread::get_id()<<"\n";
        }
        condVar.notify_all();
    }
    lck.unlock();
}

int main() {
    // Write C++ code here
    // std::cout << "Hello world!";
    thread th1();
    vector<thread>v;
    
    // for(int i=0; i < 10; i++){
        v.push_back(thread(print,0));//even
        v.push_back(thread(print,1));
    // }
        for(int i=0; i < 2; i++){
        v[i].join();
    }
    cout<<"Sum="<<sum;
    return 0;
}