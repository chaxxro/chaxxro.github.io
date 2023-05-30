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

条件变量 `std::condition_variable` 提供了两类操作：`wait` 和 `notify`

- `wait` 是线程的等待动作，直到其它线程将其唤醒后，才会继续往下执行，只接受锁  `unique_lock<mutex>`

```cpp
// std::condition_variable 提供了两种 wait() 函数
 
void wait (unique_lock<mutex>& lck);

// 只有当 pred 条件为 false 时调用 wait() 才会阻塞当前线程
// 并且在收到其他线程的通知后只有当 pred 为 true 时才会被解除阻塞
template <class Predicate>
void wait (unique_lock<mutex>& lck, Predicate pred);


std::mutex mutex;
std::condition_variable cv;

// 条件变量与临界区有关，用来获取和释放一个锁，因此通常会和 mutex 联用
std::unique_lock lock(mutex);  // 获得锁

// 当前线程调用 wait() 后将被阻塞
cv.wait(lock);  // 调用该函数前，当前线程应该已经对unique_lock<mutex> lck完成了加锁
// 线程阻塞时，会释放 lock，然后在 cv 上等待，直到其它线程通过 cv.notify_xxx来唤醒当前线程
// 释放锁后使得其他被阻塞在锁竞争上的线程得以继续执行
// cv 被唤醒后会再次对 lock 进行上锁，然后 wait 函数才会返回
// wait 返回后可以安全的使用 mutex 保护的临界区内的数据，此时 mutex 仍为上锁状态
```

- `notify` 唤醒 `wait` 在该条件变量上的线程，有 `notify_one` 唤醒一个等待的线程（多个线程阻塞时唤醒某个不确定的线程）和 `notify_all` 唤醒所有等待的线程

```cpp
std::mutex mutex;
std::condition_variable cv;

std::unique_lock lock(mutex);
// 所有等待在cv变量上的线程都会被唤醒。但直到lock释放了mutex，被唤醒的线程才会从wait返回。
cv.notify_all(lock)
```

- `std::condition_variable_any` 的 `wait()` 函数可以接受任务 lockable 参数

- `std::notify_all_at_thread_exit` 当调用该函数的线程退出时，所有在 cond 条件变量上等待的线程都会收到通知