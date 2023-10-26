---
toc:
  enable: true
  number: false
  max_depth: 3
title: condition_variable
date: 2023-05-29 21:18:57
tags: cpp
categories: cpp
---

## condition_variable

条件变量 `std::condition_variable` 提供了两类操作：`wait` 和 `notify`

- `wait` 是线程的等待动作，直到其它线程将其唤醒后，才会继续往下执行，只接受锁 `std::unique_lock<std::mutex>`

- `notify` 唤醒 `wait` 在该条件变量上的线程，有 `notify_one` 唤醒一个等待的线程和 `notify_all` 唤醒所有等待的线程

```cpp
// std::condition_variable 提供了两种 wait() 函数
void wait (std::unique_lock<std::mutex>& lck);
// 只有当 pred 条件为 false 时调用 wait() 才会阻塞当前线程
// 并且在收到其他线程的通知后只有当 pred 为 true 时才会被解除阻塞
template <class Predicate>
void wait (std::unique_lock<std::mutex>& lck, Predicate pred);
// 等价于
while (!pred()) {
    wait(lock);
}

// 条件变量与临界区有关，用来获取和释放一个锁，因此通常会和 mutex 联用
std::mutex mutex;
std::condition_variable cv;
std::unique_lock lock(mutex);  // 获得锁
// 调用该函数前当前线程应该已经完成了加锁
// 当前线程调用 wait() 后将被阻塞
cv.wait(lock);  
// 线程阻塞后会释放 lock，然后在 cv 上等待，直到其它线程通过 cv.notify_xxx来唤醒当前线程
// 释放锁后使得其他被阻塞在锁竞争上的线程得以继续执行
// cv 被唤醒后会会再次对 lock 进行上锁，然后 wait 函数才会返回
// wait 返回后可以安全的使用 mutex 保护的临界区内的数据，此时 mutex 仍为上锁状态

std::condition_variable cv;
std::mutex cv_m; // This mutex is used for three purposes:
                 // 1) to synchronize accesses to i
                 // 2) to synchronize accesses to std::cerr
                 // 3) for the condition variable cv
int i = 0;
 
void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Waiting... \n";
    cv.wait(lk, []{return i == 1;});
    std::cerr << "...finished waiting. i == 1\n";
}
 
void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        std::cerr << "Notifying...\n";
    }
    cv.notify_all();
 
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv.notify_all();
}
 
int main()
{
    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    t1.join(); 
    t2.join(); 
    t3.join();
    t4.join();
}
```
## condition_variable_any

`std::condition_variable_any` 的 `wait()` 函数可以接受任何 lockable 参数

## notify_all_at_thread_exit

 当调用 `std::notify_all_at_thread_exit` 该函数的线程退出时，所有在 cond 条件变量上等待的线程都会收到通知