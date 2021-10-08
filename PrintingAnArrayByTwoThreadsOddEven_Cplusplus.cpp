// Online C++ compiler to run C++ program online
/*
At a given time either counbt is odd or even, so at a given time only one thread is operating on array, so this method is sequential instead
of parallel. 
this kind of setup is only useful when something is to be done after the unlock happens and the lock becomes free while 
the htread ios working opn something

lock()
	cond.wait()
	dequeu
	cond.notify_all()
unlock()
----do some processing with the dequeud material which needs not be put in lock------

In such a case this implementation serves multithreading benefit and parallelism is better
*/

#include <iostream>
#include <thread>
#include<vector>
#include<mutex>
#include<condition_variable>
using namespace std;
std::condition_variable condVar;
std::mutex mtx;
const int N=10;
int a[N]={1,2,3,4,5,6,7,8,9,10};
int count=0;
int even=0, odd=0;

void print(bool isEven){
    unique_lock<mutex> lck(mtx);
    while(count<N){
    
        condVar.wait(lck,[&isEven](){return (count & 1)==isEven;});
        if(count<N)//need to chjeck this otherwise count=10
        cout<<a[count++]<<":"<<this_thread::get_id()<<" ,count value="<<count<<"\n";
        condVar.notify_all();
    }
    lck.unlock();
}

int main() {

    vector<thread>v;

        v.push_back(thread(print,0));//even
        v.push_back(thread(print,1));
        for(int i=0; i < 2; i++){
        v[i].join();
    }
    return 0;
}