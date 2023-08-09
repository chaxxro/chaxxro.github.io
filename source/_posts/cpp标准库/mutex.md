---
toc:
  enable: true
  number: false
  max_depth: 3
title: mutex
date: 2023-05-29 21:20:52
tags: cpp
categories: cpp
---

用于提供对共享变量的互斥访问

名称|用途
:-:|:-:
std::mutex|最基本也是最常用的互斥类
std::recursive_mutex|允许同一个线程对互斥量多次上锁（即递归上锁），来获得对互斥量对象的多层所有权
std::timed_mutex|除具备 mutex 功能外，还提供了带时限请求锁定的功能
std::recursive_timed_mutex|同一线程可递归的 timed_mutex

与 `std::thread` 一样，`mutex` 相关类不支持拷贝构造、不支持赋值，同时 `mutex` 类也不支持 `move` 语义(move 构造、move 赋值)

## mutex 通用操作

`lock`、`try_lock`、`unlock` 四个 `mutex` 都支持这些操作，但是不同类在行为上有些微区别

- `lock` 锁住 `mutex`

- 如果互斥量没有被锁住，则调用线程将该 `mutex` 锁住，直到调用 `unlock` 之前，该线程一直拥有该锁

- 如果 `mutex` 已被其它线程 `lock`，则调用线程将被阻塞，直到其它线程 `unlock` 该 `mutex`

- 如果当前 `mutex` 已经被当前线程锁住，则 `std::mutex` 产生死锁，而 `recursive` 系列则成功返回

## `try_lock` 尝试锁住 `mutex`

- 如果互斥量没有被锁住，则调用线程将该 `mutex` 锁住（返回 `true`），直到该线程调用 `unlock` 释放

- 如果 `mutex` 已被其它线程 `lock`，则调用线程将失败，并返回 `false`，但不会被阻塞

- 如果当前 `mutex` 已经被当前线程锁住，则 `std::mutex` 死锁，而 `recursive` 系列则成功返回 `true`

## `unlock` 解锁 `mutex`

释放对 `mutex` 的所有权

对于 `recursive` 系列 `mutex`，`unlock` 次数需要与 `lock` 次数相同才可以完全解锁

```cpp
#include <iostream>
#include <thread>
#include <mutex>

void inc(std::mutex &mutex, int loop, int &counter) {
    for (int i = 0; i < loop; i++) {
        mutex.lock();
        ++counter;
        mutex.unlock();
    }
}
int main() {
    std::thread threads[5];
    std::mutex mutex;
    int counter = 0;

    for (std::thread &thr: threads) {
        thr = std::thread(inc, std::ref(mutex), 1000, std::ref(counter));
    }
    for (std::thread &thr: threads) {
        thr.join();
    }

    // 输出：5000，如果inc中调用的是try_lock，则此处可能会<5000
    std::cout << counter << std::endl;
    return 0;
}
```

## 仅用于 timed 系列操作

`try_lock_for`、`try_lock_until` 仅用于 `timed` 系列的 mutex（`std::timed_mutex`,`std::recursive_timed_mutex`），函数最多会等待指定的时间，如果仍未获得锁，则返回 `false`。除超时设定外，这两个函数与 `try_lock` 行为一致

```cpp
// 等待指定时长
template <class Rep, class Period>
    try_lock_for(const chrono::duration<Rep, Period>& rel_time);
// 等待到指定时间
template <class Clock, class Duration>
    try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);
```

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

void run500ms(std::timed_mutex &mutex) {
    auto _500ms = std::chrono::milliseconds(500);
    if (mutex.try_lock_for(_500ms)) {
        std::cout << "获得了锁" << std::endl;
    } else {
        std::cout << "未获得锁" << std::endl;
    }
}
int main() {
    std::timed_mutex mutex;

    mutex.lock();
    std::thread thread(run500ms, std::ref(mutex));
    thread.join();
    mutex.unlock();

    return 0;
}
```

## std::try_lock

当有多个 mutex 需要执行 `try_lock` 时，该函数提供了简便的操作，`try_lock` 会按参数从左到右的顺序，对 mutex 顺次执行 `try_lock` 操作,当其中某个 `mutex.try_lock()` 失败(返回 `false` 或抛出异常)时，已成功锁定的 mutex 都将被解锁
该函数成功时返回-1， 否则返回失败 mutex 的索引，索引从 0 开始计数

```cpp
template <class L1, class L2, class... L3>
  int try_lock(L1&, L2&, L3&...);
```

## std::lock

批量上锁方式，采用死锁算法来锁定给定的mutex列表，避免死锁，上锁顺序是不确定的
该函数保证: 如果成功，则所有mutex全部上锁，如果失败，则全部解锁

```cpp
template <class L1, class L2, class... L3>
  void lock(L1&, L2&, L3&...);
```