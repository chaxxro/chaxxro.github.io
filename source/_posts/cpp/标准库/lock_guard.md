---
toc:
  enable: true
  number: false
  max_depth: 3
title: lock_guard
date: 2023-05-29 21:20:24
tags: cpp
categories: cpp
---

`lock_guard` 利用了 C++ RAII 的特性，在构造函数中上锁，析构函数中解锁，从而保证了一个已锁的互斥量总是会被正确的解锁

```cpp
template <class Mutex> class lock_guard

/*
Mutex 代表互斥量，可以是 std::mutex、std::timed_mutex、std::recursive_mutex、std::recursive_timed_mutex 中的任何一个，也可以是 std::unique_lock，都提供了 lock 和 unlock 的能力

lock_guard 仅用于上锁、解锁，不对 mutex 承担供任何生周期的管理，因此在使用的时候，请确保 lock_guard 管理的 mutex 一直有效
*/

lock_guard(lock_guard const&) = delete;
lock_guard& operator=(lock_guard const&) = delete;
```

```cpp
std::mutex my_lock;

void add(int &num, int &sum)
{
    while(true)
    {
        std::lock_guard<std::mutex> lock(my_lock);  
        if (num < 100)
        { 
            //运行条件
            num += 1;
            sum += num;
        }   
        else 
        {  
            //退出条件
            break;
        }   
    }   
}

int main()
{
    int sum = 0;
    int num = 0;
    std::vector<std::thread> ver;   //保存线程的vector
    for(int i = 0; i < 20; ++i)
    {
        std::thread t = std::thread(add, std::ref(num), std::ref(sum));
        ver.emplace_back(std::move(t)); //保存线程
    }   

    std::for_each(ver.begin(), ver.end(), std::mem_fn(&std::thread::join)); //join
    std::cout << sum << std::endl;
}
```