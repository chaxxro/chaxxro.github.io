---
toc:
  enable: true
  number: false
  max_depth: 3
title: pthread_mutex_xx
date: 2023-05-31 21:18:17
tags: LinuxApi
categories: LinuxApi
---

## 创建

```cpp
// 使用 PTHREAD_MUTEX_INITIALIZER
pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;

// 使用 pthread_mutex_init
int pthread_mutex_init(pthread_mutex_t* mutex, 
                       const pthread_mutexattr_t* attr);
```

`pthread_mutexattr_t` 为 互斥体的属性

## 销毁

不再需要互斥体时需要销毁它

```cpp
int pthread_mutex_destory(pthread_mutex_t* mutex);
```

- 无须销毁使用 `PTHREAD_MUTEX_INITIALIZER` 获得的互斥体

- 不要销毁一个已经加锁或正在被条件变量使用的互斥体，否者会返回 `EBUSY` 错误

## 加解锁

```cpp
int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_trylock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t* mutex);
```

## 属性

创建 `pthread_mutexattr_t` 时，需要调用 `pthread_mutexattr_init` 进行初始化

销毁 `pthread_mutexattr_t` 时使用 `pthread_mutexattr_destroy` 进行销毁

```cpp
int pthread_mutexattr_init(pthread_mutexattr_t* attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t* attr);
```

使用 `pthread_mutexattr_settype` 设置属性，使用 `pthread_mutexattr_gettype` 获取属性

```cpp
int pthread_mutexattr_settype(pthread_mutexattr_t* attr,
                              int type);
int pthread_mutexattr_gettype(pthread_mutexattr_t* attr,
                              int* type);
```

|属性|说明|
|-|-|
`PTHREAD_MUTEX_NORMAL`|默认属性，在一个线程加锁后，其他线程包括本线程的加锁操作回阻塞，直到互斥体被释放锁
`PTHREAD_MUTEX_ERRORCHECK`|同一线程对互斥体加锁后，再次加锁会返回 `EDEADLK`，其他线程加锁时会阻塞
`PTHREAD_MUTEX_RECURSIVE`|允许同一线程对持有的互斥体重复加锁，每次加锁其引用计数加 1，每次解锁其引用次数减 1，当引用次数为 0 时允许其他线程获得锁