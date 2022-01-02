#include <cstdio>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

void worker(int& counter, mutex& m){
    for(int i = 0; i < 1000000; i++){
        m.lock();
        counter += 1;
        m.unlock();
    }
}

int main()
{
    int counter = 0;
    mutex m;
    vector<thread> workers;
    auto start = std::chrono::steady_clock::now();
    for(int i = 0; i < 4; i++){
        workers.push_back(thread(worker, ref(counter), ref(m)));
    }
    for(int i = 0; i < 4; i++){
        workers[i].join();
    }
    auto end = std::chrono::steady_clock::now();
    auto etime = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    cout << counter << " 시간 : " << etime << " milliseconds";
}