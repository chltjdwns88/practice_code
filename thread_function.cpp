#include <cstdio>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

void workers(vector<int>::iterator start, vector<int>::iterator end, int* result, int index){
    int sum = 0;
    for(auto iter = start; iter < end; iter++){
        sum += *iter;
    }
    *result = sum;
    // cout << "thread " << index << "의 합은 : " << sum << '\n';
    printf("%s %d 의 합은 : %d\n", "thread", index, sum);
}

int main()
{
    vector<int> data(10000);
    for(int i = 0; i < data.size(); i++){
        data[i] = i+1;
    }
    vector<int> partition_sum(4);
    
    vector<thread> worker;
    int index = 1;
    auto start = std::chrono::steady_clock::now();
    for(int i = 0; i < partition_sum.size(); i++){
        worker.push_back(thread(workers, data.begin()+i*2500, data.begin()+(i+1)*2500, &partition_sum[i], index++));
    }

    for(int j = 0; j < worker.size(); j++){
        worker[j].join();
    }
    auto end = std::chrono::steady_clock::now();
    auto etime = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    int total_sum = 0;
    for(int k = 0; k < partition_sum.size(); k++){
        total_sum += partition_sum[k];
    }
    cout << "총합 : " << total_sum;
    cout << "총 걸린 시간 : " << etime << "milliseconds";
}