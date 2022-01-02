#include <iostream>
#include <mutex>
#include <thread>

void func1(){
    for(int i = 0; i < 10; i++)
        std::cout << "쓰레드 1 실행중" << '\n';
}

void func2(){
    for(int i = 0; i < 10; i++)
        std::cout << "쓰레드 2 실행중" << '\n';
}

void func3(){
    for(int i = 0; i < 10; i++)
        std::cout << "쓰레드 3 실행중" << '\n';
}

int main()
{
    std::thread t1(func1);
    std::thread t2(func2);
    std::thread t3(func3);

    t1.join();
    t2.join();
    t3.join();  //thread 종료시 return
    return 0;
}