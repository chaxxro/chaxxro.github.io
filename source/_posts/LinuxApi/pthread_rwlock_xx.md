---
toc:
  enable: true
  number: false
  max_depth: 3
title: pthread_rwlock_xx
date: 2023-05-31 21:22:17
tags: LinuxApi
categories: LinuxApi
---

## 创建

```cpp
// 方式一
pthread_rwlock_t rw = PTHREAD_RWLOCK_INITIALIZER;

// 方式二
int pthread_rwlock_init(pthread_rwlock_t* rw,
                        const pthread_rwlockattr_t* attr);
```

## 属性

```cpp
// 初始化
int pthread_rwlockattr_init(pthread_rwlockattr_t* attr);

// 销毁
int pthread_rwlockattr_destroy(pthread_rwlockattr_t* attr);

// 查询
int pthread_rwlockattr_getkind_np(const pthread_rwlockattr_t* attr,
                                  int* pref);

// 设置
int pthread_rwlockattr_setkind_np(const pthread_rwlockattr_t* attr,
                                  int pref);

enum {
    // 读优先，即读写同时请求时，读获得锁
    PTHREAD_RWLOCK_PREFER_READER_NP,
    // 还是读优先
    PTHREAD_RWLOCK_PREFER_WRITER_NP,
    // 写优先，即读写同时请求时，写获得锁
    PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
    PTHREAD_RWLOCK_PREFER_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
}
```

## 销毁

```cpp
int pthread_rwlock_destroy(pthread_rwlock_t* rw);
```

## 请求读锁

```cpp
int pthread_rwlock_rdlock(pthread_rwlock_t* rw);

int pthread_rwlock_tryrdlock(pthread_rwlock_t* rw);

int pthread_rwlock_timedrdlock(pthread_rwlock_t* rw,
                               const struct timespec* abstime);
```

读锁用于共享模式

如果当前锁被读模式占用，则其他线程请求读锁会立即获得锁，其他线程请求写锁会阻塞

## 请求写锁

```cpp
int pthread_rwlock_wrlock(pthread_rwlock_t* rw);

int pthread_rwlock_trywrlock(pthread_rwlock_t* rw);

int pthread_rwlock_timedwrlock(pthread_rwlock_t* rw,
                               const struct timespec* abstime);
```

写锁用于独占模式

如果当前锁被写模式占用，则其他线程无论请求读锁还是写锁都会阻塞

## 释放锁

```cpp
int pthread_rwlock_unlock(pthread_rwlock_t* rw);
```
