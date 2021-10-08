// Online C++ compiler to run C++ program online
/*
This is parallel addition of diaganols of an array
*/
#include <iostream>
#include <thread>
#include<vector>
#include<mutex>
#include<condition_variable>

#define thread_num 5
using namespace std;
// std::condition_variable condVar;
std::mutex mtx;
const int N=10;
// int a[N]={1,2,3,4,5,6,7,8,9,10};
int b[N][N];

    
// int b[N][N]={
//     {1,2,3,4},
//     {1,2,3,4},
//     {1,2,3,4},
//     {1,2,3,4}
// };





void print(int* arg){
    cout<<"value of arg="<<*arg<<"\n";
    int sum=0, count=0;
    while(*arg<N){
        int count=*arg;
            if(count==(N-1-count))
                sum+=b[count][count];
            else
                sum+=(b[count][count]+b[count][N-1-count]);
            cout<<"Adding: b["<<count<<"]"<<"["<<count<<"]"<<" and b["<<count<<"]"<<"["<<(N-1-count)<<"]"<<":"<<this_thread::get_id()<<"\n";
            count+=thread_num;
            *arg=count;
            cout<<"incremeneted arg="<<*arg<<"\n";

    }
    delete arg;
}

int main() {
    for(int i=0; i < N; i++)
    for(int j=0; j < N ; j++)
        b[i][j]=j+1;
    vector<thread>v;
    for(int i=0; i < thread_num; i++){
        int *arg=new int(i);
        v.push_back(thread(print,arg));
    }
        for(int i=0; i < thread_num; i++){
        v[i].join();
    }
    // cout<<"Sum="<<sum;
    return 0;
}