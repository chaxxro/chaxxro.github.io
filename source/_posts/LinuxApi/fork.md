---
toc:
  enable: true
  number: false
  max_depth: 3
title: fork
date: 2023-05-31 21:17:01
tags: LinuxApi
categories: LinuxApi
---

调用 `fork()` 函数时，复制父进程的进程空间来创建子进程

父进程空间代码段是不会复制到子进程的，而是共享；其它段需要复制，包括进程上下文、进程堆栈、内存信息、打开的文件描述符、信号控制设定、进程优先级、进程组号等，属于写拷贝（COW，即只有改的时候, 才需要拷贝），这样提高效率, 节省资源，相当于克隆了一个自己

在 `fork()` 函数执行完毕后有两个进程，一个是子进程，一个是父进程；在子进程中，`fork()` 函数返回 0，在父进程中，`fork()` 返回子进程的进程 ID；因此可以通过 `fork()` 返回的值来判断当前进程是子进程还是父进程，从而让它们同时干不同的事情

所有由父进程打开的文件描述符都被复制到子进程中，父、子进程中相同编号的文件描述符在内核中指向同一个 file 结构体，也就是说，file 结构体的引用计数要增加

父子进程的执行顺序是由操作系统调度的，谁先执行并不确定

`vfork()` 函数不复制父进程的进程空间，而是抢占父进程的资源，导致父进程堵塞，无法继续运行，子进程完成后，父进程才能继续运行

`clone()` 可以让有选择性的继承父进程的资源，可以选择想 `vfork()` 一样和父进程共享一个虚存空间，也可以不和父进程共享，甚至可以选择创造出来的进程和父进程不再是父子关系，而是兄弟关系

`fork()`、`clone()`、`vfork()` 的内部实际都是调用一个内核内部函数 `do_fork()`，只是填写的参数不同而已

## wait 函数

`wait()` 函数等待子进程的结束信号；阻塞函数，只有任意一个子进程结束，它才能继续往下执行

`waitpid()` 可以选择等指定等待哪个子进程结束，还可以选择等待方式(堵塞、不堵塞)

## exec 系列函数

`fork()`、`vfork()` 产生的子进程内容和父进程完全一致，使用 `exec()` 系列函数载入二进制映像，替换当前进程的映像，使子进程执行不同的程序

使用 `vfork()` 堵塞父进程，抢了资源，但是使用 `exec()` 后，子进程替换了内容，便不抢占资源了，父进程继续执行，不用等子进程

## fork 与多线程

在多线程执行的情况下调用 `fork()`，仅会将发起调用的线程复制到子进程中，子进程中该线程的 ID 与父进程中发起 `fork()` 调用的线程 ID 是一样的

其他线程均在子进程中立即停止并消失，并且不会为这些线程调用清理函数以及针对线程局部存储变量的析构函数

1. 虽然只将发起 `fork()` 调用的线程复制到子进程中，但全局变量的状态以及所有的 `pthreads` 对象（如互斥量、条件变量等）都会在子进程中得以保留，这样容易导致死锁和全局变量未初始化成功

2. 未执行清理函数和针对线程局部存储数据的析构函数，所以多线程情况下可能会导致子进程的内存泄露

pthreads API 提供了一种机制，利用函数 `pthread_atfork()` 来创建 `fork()` 处理函数

```cpp
// @prepare 新进程产生之前被调用
// @parent  新进程产生之后在父进程被调用
// @child    新进程产生之后，在子进程被调用
int pthread_atfork (void (*prepare) (void), void (*parent) (void), void (*child) (void));
```

该函数的作用就是往进程中注册三个函数，以便在不同的阶段调用，有了这三个参数，就可以在对应的函数中加入对应的处理功能

每次调用 `pthread_atfork()` 函数会将 `prepare` 添加到一个函数列表中，创建子进程之前会（按与注册次序相反的顺序）自动执行该函数列表中函数

`parent` 与 `child` 也会被添加到一个函数列表中，在 `fork()` 返回前，分别在父子进程中自动执行（按注册的顺序）