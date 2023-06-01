---
toc:
  enable: true
  number: false
  max_depth: 3
title: pthread_xx
date: 2023-05-31 21:25:04
tags: LinuxApi
categories: LinuxApi
---

## 创建线程

```cpp
int  pthread_create(pthread_t* thread,
                    const pthread_attr_t* attr,
                    void *(*start_routine) (void*),
                    void* arg);
```

- `thread` 参数是一个输出参数，如果线程创建成功，则可以通过该参数获取线程 ID

- `attr` 指定该线程的属性，默认使用 `nullptr`

- `start_routine` 指定线程函数，该函数的顶用方式必须是 `__cdecl`，`__cdecl` 是 C/C++ 全局函数的默认调用方式，函数签名为 `void* func(void*)`

- `arg` 用于创建线程时传入线程函数，`void*` 方便将任意信息传入线程函数

## 获取线程 ID

线程 ID 在整个操作系统中唯一的，可以在当前线程调用 `pthread_self()` 获取当前线程的线程 ID

```cpp
// 方法一
pthread_t pthread_self(void);

// 方法二
#include <sys/syscall.h>
#include <unistd.h>
int tid = syscall(SYS_gettid);
```

`pthread_t` 是一块内存的空间地址，由于不同进程可能有同样地址的内存快，因此 `pthread_t` 可能不是全局唯一的，一般是个很大的数字

通过方法二获取的线程 ID 是系统范围的全局唯一

## join

系统提供了 `pthread_join` 用来等待某个线程的退出并接受返回值

```cpp
int pthread_join(pthread_t* thread, void** retval);
```

- `thread` 为需要等待的线程 ID

- `retval` 为输出参数，用于接收等待退出的线程的推出码，可以调用 `pthread_exit` 指定线程退出时退出码，也可以 `return` 返回线程推出码

```cpp
void pthread_exit(void* value_ptr);
```

`pthread_join` 在等待目标线程退出期间会挂起当前线程，被挂起的线程处于等待状态，不消耗 CPU 时间片

目标线程退出后，调用 `pthread_join` 线程才会被唤醒

## 属性

`pthread_attr_t` 需使用 `pthread_attr_init` 初始化

`pthread_attr_t` 需使用 `pthread_attr_destroy` 销毁

```cpp
typedef struct {
    int                       detachstate;   // 线程的分离状态
    int                       schedpolicy;   // 线程调度策略
    structsched_param         schedparam;    // 线程的调度参数
    int                       inheritsched;  // 线程的继承性
    int                       scope;         // 线程的作用域
    size_t                    guardsize;     // 线程栈末尾的警戒缓冲区大小
    int                       stackaddr_set; // 线程的栈设置
    void*                     stackaddr;     // 线程栈的位置
    size_t                    stacksize;     // 线程栈的大小
} pthread_attr_t;

// 设置方法
int pthread_attr_getdetachstate(const pthread_attr_t* attr, 
                                int* detachstate);
int pthread_attr_setdetachstate(pthread_attr_t* attr,
                                int detachstate);

int pthread_attr_getinheritsched(const pthread_attr_t* attr,
                                 int* inheritsched);
int pthread_attr_setinheritsched(pthread_attr_t* attr,
                                 int inheritsched);

int pthread_attr_getschedpolicy(const pthread_attr_t *, 
                                int * policy);
int pthread_attr_setschedpolicy(pthread_attr_*, int policy);

int pthread_attr_getschedparam(const pthread_attr_t*,
                               struct sched_param*);
int pthread_attr_setschedparam(pthread_attr_t*,
                               const struct sched_param*);

int pthread_attr_getscope(const pthread_attr_t* attr, 
                          int* scope);
int pthread_attr_setscope(pthread_attr_t*, int);

int pthread_attr_getstacksize(const pthread_attr_t*,
                              size_t * stacksize);
int pthread_attr_setstacksize(pthread_attr_t*,
                              size_t* stacksize);

int pthread_attr_getstackaddr(const pthread_attr_t* attr,
                              void **stackaddf);
int pthread_attr_setstackaddr(pthread_attr_t* attr,
                              void* stackaddr);
```

- `detachstate` 表示新线程是否与进程中其他线程脱离同步，如果设置为 `PTHREAD_CREATE_DETACHED` 则新线程不能用 `pthread_join()` 来同步，且在退出时自行释放所占用的资源，缺省为 `PTHREAD_CREATE_JOINABLE` 状态，该属性可以通过线程创建并运行以后用 `pthread_detach()` 来设置

- `schedpolicy` 表示新线程的调度策略，主要包括 `SCHED_OTHER`（正常、非实时）、`SCHED_RR`（实时、轮转法）和 `SCHED_FIFO`（实时、先入先出）三种，缺省为 `SCHED_OTHER`，运行时可以用过 `pthread_setschedparam()` 来改变

- `schedparam` 线程调度参数，目前仅有一个 `sched_priority` 整型变量表示线程的运行优先级，仅当调度策略为 `SCHED_RR` 或 `SCHED_FIFO` 时才有效，并可以在运行时通过 `pthread_setschedparam()` 函数来改变，缺省为 0

- `inheritsched` 表示可继承性，有 `PTHREAD_EXPLICIT_SCHED` 和 `PTHREAD_INHERIT_SCHED` 两种，前者表示新线程使用显式指定调度策略和调度参数，而后者表示继承调用者线程的值，缺省为 `PTHREAD_EXPLICIT_SCHED`

- `scope` 表示线程间竞争 CPU 的范围，目前仅实现了 `PTHREAD_SCOPE_SYSTEM`，表示与系统中所有线程一起竞争 CPU 时间

## 惯用法

线程函数的签名必须是指定格式，如果使用 C++ 面向对象的方式对线程函数进行封装，线程函数就不能是类的成员方法，只能是静态方法

编译器在编译成员方法时，会将成员方法编译成全局方法，然后在形参列表中添加类的实例对象指针，因此不再符合线程函数的函数签名需求

```cpp
class Thread {
public:
    void* threadFunc(void* arg)
}

// 编译翻译成
void* threadFunc(Thread* this, void* arg);
```

因此在实际应用中，在创建线程时将当前对象的地址传递给线程函数，然后在线程函数中将该指针转换为原来的类实例，再通过这个类实例访问类的所有方法

```cpp
class CThread {
public:
    CThread();
    virtual ~CThread();

    virtual bool Create();

    pthread_t GetHandle();

private:
    virtual bool InitInstance();

    virtual void ExitInstance();

    virtual void Run() = 0;

    static void* _ThreadEntry(void* arg);

private:
    pthread_t m_thread;
}

void* CThread::_ThreadEntry(void* arg) {
    CThread* pThread = (CThread*)arg;
    if (pThread->InitInstance()) pThread->Run();
    pThread->ExitInstance();
    return nullptr;
}

CThread::CThread() {
    m_thread = (pthread_t)0;
    m_id = 0;
}

CThread::~CThread() {

}

bool CThread::Create() {
    if (m_thread != (pthread_t)0) return true;
    bool res = true;
    res = pthread_create(&m_thread, nullptr, &_ThreadEntry, this) == 0;
    retrun res;
}

bool CThread::InitInstance() {
    return true;
}

void CThread::ExitInstance() {}
```