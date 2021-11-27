#include <iostream>
#include <thread>
#include <array>
#include <mutex>
#include <atomic>

/**
* (1)临界资源
* 1. 互斥锁 mutex， pthread_mutex_t
* 2. 自旋锁 spinlock, 
* 3. 原子操作
* 
* (2)多线程++问题
* 1. ++的多条汇编指令发生穿插
* 2. 线程切换,CPU切换，一个线程：寄存器的值=>上下文中  &&  另一个线程：上下文中的值=>寄存器中。
*   move allregister
*   ucontext
*   setjump/longjump
* 
* (3)thread没有拷贝构造，有移动构造
* 
* (4)mutex，操作时间比较长【线程资源会被切走】
* spinlock，操作时间比较短【线程资源不会切走】
*     操作时间短于线程切换时间。
* 
* (5)原子操作，封装部分操作语句 => 单条指令。
*     C++11的关键字。
* 
* (6)线程安全的单例模式：CAS(compare and swap)
*     if (a == b) a = c
*     if (instance == NULL) instance = malloc();
*/

using namespace std;
int count1 = 0;
mutex m1;
void run_lock() {
    for (int i = 0; i < 0xFFFFFFFF; i++) {
        {
            unique_lock<mutex> ul(m1);   //17256
            count1++;                    //12355
        }    
        std::this_thread::yield();
        //m1.unlock();
        //this_thread::sleep_for(chrono::nanoseconds(1));
    }
}

int inc(int* value, int add) {
    int old = 0;
#if 0
    __asm  volatile(
        "lock; xaddl %2, %1;"
        : "=a" (old)
        : "m"  (*value), "a"(add)
        : "cc", "memory"
    );
#endif
    return old;
}
atomic<int> count2(0);
void run_atmoc() {
    for (int i = 0; i < 1000000; i++) {
        //m1.lock();   //17256
        count2++;      //12355
        //m1.unlock();
        std::this_thread::yield();
        //this_thread::sleep_for(chrono::nanoseconds(1));
    }
}

void run() {
    for (int i = 0; i < 1000000; i++) {
        //m1.lock();   //17256
        count1++;      //12355
        //m1.unlock();
        //this_thread::sleep_for(chrono::nanoseconds(1));
        std::this_thread::yield();
    }
}

int main()
{
    array<thread, 10> arr_thread;
    auto start = clock();
    for (int i = 0; i < 10; i++) {
        arr_thread[i] = thread(run_atmoc);
    }
    
    for (int i = 0; i < 10; i++) {
        cout << count2 << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    auto end = clock();

    cout << "cost : " <<  end - start << endl;

    for (int i = 0; i < 10; i++) {
        arr_thread[i].join();
    }

    return 0;
}
