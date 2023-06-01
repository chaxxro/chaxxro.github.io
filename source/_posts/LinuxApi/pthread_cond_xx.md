---
toc:
  enable: true
  number: false
  max_depth: 3
title: pthread_cond_xx
date: 2023-05-31 21:15:17
tags: LinuxApi
categories: LinuxApi
---

## 初始化

```cpp
// 方式一
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// 方式二
int pthread_cond_init(pthread_cond_t* cond, 
                      const pthread_condattr_t* attr);
```

## 销毁

```cpp
int pthread_cond_destroy(pthread_cond_t* cond);
```

## 等待

```cpp
int pthread_cond_wait(pthread_cond_t* cond,
                      pthread_mutex_t mutex);

int pthread_cond_timewait(pthread_cond_t* cond,
                          pthread_mutex_t* mutex,
                          const struct timespec* abs_time);
```

`pthread_cond_wait` 阻塞时，会释放绑定的互斥体并阻塞线程

`pthread_cond_wait` 返回时会对绑定的互斥体加锁

## 唤醒

```cpp
int pthread_cond_signal(pthread_cond_t* cond);

int pthread_cond_broadcast(pthread_cond_t* cond);
```

`pthread_cond_signal` 唤醒一个线程，但具体哪个线程不确定

`pthread_cond_broadcast` 唤醒所有线程

## 虚假唤醒

操作系统可能在某些情况下唤醒条件变量，即存在没有其他线程向条件变量发送信号，但等待的线程被唤醒的情况，因此需要在被唤醒后再次检测条件

这是因为 `pthread_cond_wait` 是阻塞型系统调用，当被信号中断时会返回 -1，并把 `errno` 置为 `EINTR`

因此在被中断唤醒后到再次调用 `pthread_cond_wait` 前会丢失信号，则有可能无限等待

解决方法：在条件变量唤醒后，使用 `while` 检查条件是否满