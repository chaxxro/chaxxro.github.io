---
toc:
  enable: true
  number: false
  max_depth: 3
title: epoll
date: 2023-04-26 20:48:54
tags: LinuxApi
categories: LinuxApi
---

`epoll` 比 `select` 和 `poll` 更加灵活而且没有描述符数量限制

`epoll` 对多线程编程更有友好，一个线程调用了 `epoll_wait()`，另一个线程关闭了同一个描述符也不会产生像 `select()` 和 `poll()` 的不确定情况

`epoll()` 分清了频繁调用和不频繁调用的操作，`epoll_wait()` 是非常频繁调用的，而 `epoll_ctl()` 是不太频繁调用的，不会随着并发连接的增加使得入参越发多起来，导致内核执行效率下降。

```cpp
#include <sys/epoll.h>

// 创造 epoll fd
// size 大于 0 即可
// 失败返回 -1
int epoll_create(int size);

// 注册监听事件
// op 表示对 fd 操作类型
// EPOLL_CTL_ADD（注册新的 fd 到 epfd 中）
// EPOLL_CTL_MOD（修改已注册的 fd 的监听事件）
// EPOLL_CTL_DEL（从 epfd 中删除一个 fd）
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

// 等待事件的就绪，成功时返回就绪的事件数目，调用失败时返回 -1，等待超时返回 0
// events 用来从内核得到就绪事件的集合
// maxevents 告诉内核这个 events 有多大
// timeout 表示等待时的超时时间，以毫秒为单位
// 返回值是有事件发生的 fd 数目
int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);

struct epoll_events {
    __uint32_t events;  // epoll event
    epoll_data_t data;  // user data variable
}

union epoll_data_t {
    void ptr;
    int fd;
    __uint32_t u32;
    __uint64_t u64;
}
/*
epoll_event  被用于注册所感兴趣的事件和回传所发生待处理的事件，其中 epoll_data_t 联合体用来保存触发事件的某个文件描述符相关的数据

events 字段是表示感兴趣的事件和被触发的事件可能的取值为：
EPOLLIN ：表示对应的文件描述符可以读；
EPOLLOUT：表示对应的文件描述符可以写；
EPOLLPRI：表示对应的文件描述符有紧急的数据可读
EPOLLERR：表示对应的文件描述符发生错误；
EPOLLHUP：表示对应的文件描述符被挂断；
EPOLLET：表示对应的文件描述符设定为edge模式；
EPOLLONESHOT：最多触发其上注册的一个可读、可写、或者异常事件，且只触发一次，使一个 socket 连接任何时刻都只被一个线程所处理，注册了 EPOLLONESHOT 事件的 socket 一旦被某个线程处理完毕，该线程就应该立即重置这个 socket 上的 EPOLLONESHOT 事件，以确保这个 socket 下一次可读
EPOLLET 通过与其他事件取或运算，使该事件成为边缘触发模式
*/

int svr_fd = get_svr_fd(10000);

int epoll_fd = epoll_create(1);

epoll_event ev = {0};
ev.data.fd = svr_fd;
ev.events = EPOLLIN;
epoll_ctl(epoll_fd, EPOLL_CTL_ADD, svr_fd, &ev);

while (1) {
  struct epoll_event pevents[20];
  int ret = epoll_wait(epoll_fd, pevents, 20, 10000);
  if (ret == -1) {
    // 错误
  } else if (ret == 0) {
    // 超时
  } else {
    for (int i = 0; i < ret; i++) {
      auto &event = pevents[i];
      if (event.events & EPOLLIN) {
        if (event.data.fd == svr_fd) {
          int cli = accept_cli(svr_fd);
          send_msg(cli);

          epoll_event cli_event;
          cli_event.data.fd = cli;
          cli_event.events = EPOLLIN;
          epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cli, &cli_event);
        } else {
          recv_msg(event.data.fd);
        }
      }
    }
  }
}
```

一般在 fd 数量比较多，但某段时间内就绪事件 fd 数量较少的情况下，`epoll_wait` 才会体现出它的优势，也就是说 socket 连接数量较大时而活跃连接较少时 epoll 模型更高效。

已注册的 fd 在内核中会被维护在一棵红黑树上，通过回调函数内核会将 IO 准备好的描述符加入到一个双向链表中管理，进程调用 `epoll_wait()` 便可以得到事件完成的描述符

`epoll` 将 fd 从进程缓冲区向内核缓冲区拷贝一次，并且进程不需要通过轮询来获得事件完成的描述符

要在内核中长久的维护一个数据结构来存放文件描述符，并且时常会有插入、查找和删除的操作发生，会对内核产生不小的影响，因此需要一种插入、查找和删除效率都不错的数据结构来存放这些文件描述符，因此选择红黑树存储 fd

在红黑树中排序的根据是 `epoll_filefd` 的地址大小

## 工作模式

epoll 的描述符事件有两种触发模式：LT（level trigger）和 ET（edge trigger）

- LT：默认的一种模式，当 `epoll_wait()` 检测到描述符事件到达时，将此事件通知进程，进程可以不立即处理该事件，下次调用 `epoll_wait()` 会再次通知进程

- ET：只会在未就绪变为就绪时触发，所以用户进程必须立即处理事件，如果不处理，则下次再调用  `epoll_wait()` 时不会再得到当前事件到达的通知

- ET 很大程度上减少了 epoll 事件被重复触发的次数，因此效率要比 LT 模式高

- LT 支持阻塞 socket 和非阻塞 socket

- ET 只支持非阻塞 socket，因为 ET 需要一次性接受完所有数据，如果使用阻塞 socket 会导致最后一次接受数据阻塞其他 socket

- 读事件：LT 模式下，可以按需收取想要的字节数，不用把本次接收到的数据收取干净，当数据未接受完时读事件仍会触发；ET 模式下，必须把数据收取干净，因为不一定有下一次机会再收取数据了，除非有新数据到达，即使后续继续触发也可能存在上次没读完的数据没有及时处理，造成客户端响应延迟，即需要循环到 `recv` 或者 `read` 函数返回 -1，错误码为 `EWOULDBLOCK` 或 `EAGAIN`，因此需搭配非阻塞 socket 使用

- 写事件：LT 模式下，不需要写事件一定要及时移除，避免不必要的触发，浪费 CPU 资源；ET 模式下，写事件只会由不可写变成可写时触发，如果需要下一次的写事件触发来驱动任务（例如发上次剩余的数据），可移除可写事件后再注册一次检测可写事件

使用 ET 模式监听 listen fd 时，因为需要一次性读取全部 fd，所以在多进程情况下容易造成负载不均衡的情况

## 使用场景

- 有大量的描述符需要同时轮询，并且这些连接最好是长连接

- 需要同时监控小于 1000 个描述符，没有必要使用 `epoll`

- 需要监控的描述符状态变化多，没有必要使用 `epoll`，因为 `epoll` 中的所有描述符都存储在内核中，造成每次需要对描述符的状态改变都需要通过 `epoll_ctl()` 进行系统调用，频繁系统调用降低效率

## 适用文件描述符类型

只有底层驱动实现了 `file_operations` 中 `poll`函数的文件类型才可以被 `epoll`监视，所以使用 `open` 打开的普通文件描述符不能被加入 `epoll

## epoll 底层中的 wq 队列

一个进程调用 `epoll_wait` 后，如果当前还没有任何事件发生，需要让当前进程放到 `wq` 里挂起等待

当 `epoll` 实例监视的文件上有事件发生后，需要唤醒 `wq` 上的进程去继续执行用户态的业务逻辑

当多个进程都在关注同一个 `epoll` 实例时，休眠的进程们通过这个等待队列就可以逐个被唤醒，从而引起惊群效应

## epoll 底层中的 poll_wait 队列

一个 `epoll` 类型的 fd 可以被其他 `epoll` 实例监视

`epoll` 类型的 fd 只会有读就绪的事件，当 `epoll` 所监视的非 `epoll` 类型文件有读就绪事件时，当前 `epoll` 也会进入读就绪状态

`poll_wait` 队列是用来处理 `epoll` 间嵌套监视的情况的，可读事件触发时需要从 `poll_wait` 队列中找到监听它的 `epoll` 实例

## epoll 底层中的锁

`epoll` 中有 3 把锁，分别是 `epmutex`、`mtx`、`lock`

### epmutex

`epmutex` 是一个全局互斥锁，`epoll` 中一共有 3 个地方用到这把锁

- `ep_free()` 销毁一个 `epoll` 实例时

- `eventpoll_release_file()` 清理从 `epoll` 中已经关闭的文件时

- `epoll_ctl()` 时避免 `epoll` 间嵌套调用时形成死锁

`epmutex` 的锁粒度最大，用来处理跨 `epoll` 实例级别的同步操作

### mtx

`mtx` 是一个 `epoll` 内部的互斥锁

- `ep_scan_ready_list()` 扫描就绪列表

- `eventpoll_release_file()` 中执行 `ep_remove()` 删除一个被监视文件

- `ep_loop_check_proc()` 检查 `epoll` 是否有循环嵌套或过深嵌套

- `epoll_ctl()` 操作被监视文件增删改等

可以看出都是涉及对 `epoll` 实例中 `rdllist` 或红黑树的访问，因此 `mtx` 是一个 `epoll` 实例内的互斥锁，用来保护 `epoll` 实例内部的数据结构的线程安全

### lock

`lock` 是一个 `epoll` 实例内部的自旋锁，用来保护 `rdllist` 的线程安全

自旋锁的特点是得不到锁时不会引起进程休眠，所以在 `ep_poll_callback` 中只能使用 `lock`，否则就会丢事件