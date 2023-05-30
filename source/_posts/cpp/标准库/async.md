---
toc:
  enable: true
  number: false
  max_depth: 3
title: async
date: 2023-05-29 21:12:12
tags: cpp
categories: cpp
---

`std::async` 用于直接创建异步任务，实际上就是创建一个线程执行相应任务，基本上可以代替 `std::thread` 的所有事情，异步任务返回的结果保存在 `std::future` 中

`std::async` 有两种重载形式

```cpp
#define FR typename result_of<typename decay<F>::type(typename decay<Args>::type...)>::type
// 用来推断函数 F 的返回值类型

// 不含执行策略
template <class F, class... Args>
future<FR> async(F&& f, Args&&... args);
// 含执行策略
template <class F, class... Args>
future<FR> async(launch policy, F&& f, Args&&... args);

// 执行策略定义了async执行F(函数或可调用求对象)的方式，是一个枚举值
enum class launch 
{
    // 保证异步行为，F将在单独的线程中执行
    // 在调用 async 时就开始创建线程
    async = 1,

    // 当其它线程调用std::future::get时，将调用非异步形式, 即F在get函数内执行
    // 延迟加载方式创建线程，直到调用 future 的 get 或 wait 时才创建线程
    deferred = 2,

    // F的执行时机由std::async来决定
    any = async | deferred
};

// 不含加载策略的版本，使用的是 std::launch::any
```

```cpp
#include <iostream>
#include <future>   // std::async, std::future
#include <chrono>   
using namespace std::chrono;

int main() 
{
    auto print = [](char c) 
    {
        for (int i = 0; i < 10; i++) 
        {
            std::cout << c;
            std::cout.flush();
            std::this_thread::sleep_for(milliseconds(1));
        }
    };

    // 不同launch策略的效果
    std::launch policies[] = {std::launch::async, std::launch::deferred};
    const char *names[] = {"async   ", "deferred"};
    for (int i = 0; i < sizeof(policies)/sizeof(policies[0]); i++) 
    {
        std::cout << names[i] << ": ";
        std::cout.flush();
        std::future<void> f1 = std::async(policies[i], print, '+');
        std::future<void> f2 = std::async(policies[i], print, '-');
        f1.get();
        f2.get();
        std::cout << std::endl;
    }
    return 0;
}

// async   : +-+-+-+--+-++-+--+-+
// deferred: ++++++++++----------
```