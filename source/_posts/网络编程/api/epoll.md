---
toc:
  enable: true
  number: false
  max_depth: 3
title: epoll
date: 2023-04-26 20:48:54
tags: 网络编程
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
epoll_event 被用于注册所感兴趣的事件和回传所发生待处理的事件，其中 epoll_data 联合体用来保存触发事件的某个文件描述符相关的数据

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

// Create the epoll descriptor. Only one is needed per app, and is used to monitor all sockets.
// The function argument is ignored (it was not before, but now it is), so put your favorite number here
int pollingfd = epoll_create( 0xCAFE );

if ( pollingfd < 0 )
// report error

// Initialize the epoll structure in case more members are added in future
struct epoll_event ev = { 0 };

// Associate the connection class instance with the event. You can associate anything
// you want, epoll does not use this information. We store a connection class pointer, pConnection1
ev.data.ptr = pConnection1;

// Monitor for input, and do not automatically rearm the descriptor after the event
ev.events = EPOLLIN | EPOLLONESHOT;
// Add the descriptor into the monitoring list. We can do it even if another thread is
// waiting in epoll_wait - the descriptor will be properly added
if ( epoll_ctl( epollfd, EPOLL_CTL_ADD, pConnection1->getSocket(), &ev ) != 0 )
// report error

// Wait for up to 20 events (assuming we have added maybe 200 sockets before that it may happen)
struct epoll_event pevents[ 20 ];

// Wait for 10 seconds, and retrieve less than 20 epoll_event and store them into epoll_event array
int ret = epoll_wait( pollingfd, pevents, 20, 10000 );
// Check if epoll actually succeed
if ( ret == -1 )
// report error and abort
else if ( ret == 0 )
// timeout; no event detected
else
{
    // Check if any events detected
    for ( int i = 0; i < ret; i++ )
    {
        if ( pevents[i].events & EPOLLIN )
        {
            // Get back our connection pointer
            Connection * c = (Connection*) pevents[i].data.ptr;
            c->handleReadEvent();
         }
    }
}
```

一般在 fd 数量比较多，但某段时间内就绪事件 fd 数量较少的情况下，`epoll_wait` 才会体现出它的优势，也就是说 socket 连接数量较大时而活跃连接较少时 epoll 模型更高效。

`epoll_ctl()` 用于向内核注册新的描述符或者是改变某个文件描述符的状态。已注册的描述符在内核中会被维护在一棵红黑树上，通过回调函数内核会将 I/O 准备好的描述符加入到一个链表中管理，进程调用 `epoll_wait()` 便可以得到事件完成的描述符

`epoll` 使用 `mmap` 减少复制开销，内核可以直接看到 `epoll` 监听的句柄，效率高

`epoll` 将用户关系的文件描述符的事件存放到内核的一个事件表中，因此只需要将描述符从进程缓冲区向内核缓冲区拷贝一次，并且进程不需要通过轮询来获得事件完成的描述符

要在内核中长久的维护一个数据结构来存放文件描述符，并且时常会有插入、查找和删除的操作发生，会对内核产生不小的影响，因此需要一种插入、查找和删除效率都不错的数据结构来存放这些文件描述符，因此选择红黑树存储文件描述符

在红黑树中排序的根据是 epoll_filefd 的地址大小

## 工作模式

epoll 的描述符事件有两种触发模式：LT（level trigger）和 ET（edge trigger）

- LT：默认的一种模式，当 `epoll_wait()` 检测到描述符事件到达时，将此事件通知进程，进程可以不立即处理该事件，下次调用 `epoll_wait()` 会再次通知进程；支持阻塞 socket 和非阻塞 socket

- ET：通知之后进程必须立即处理事件，如果不处理，则下次再调用  `epoll_wait()` 时不会再得到事件到达的通知，很大程度上减少了 epoll 事件被重复触发的次数，因此效率要比 LT 模式高；内核会假设进程知道文件描述符已经就绪，并且不会再为那个文件描述符发送更多的就绪通知，直到进程做了某些操作导致那个文件描述符不再为就绪状态；只支持非阻塞 socket

- 读事件：LT 模式下，可以按需收取想要的字节数，不用把本次接收到的数据收取干净，当数据未接受完时读事件仍会触发；ET 模式下，必须把数据收取干净，因为不一定有下一次机会再收取数据了，除非有新数据到达，即使后续继续触发也可能存在上次没读完的数据没有及时处理，造成客户端响应延迟，即需要循环到 `recv` 或者 `read` 函数返回 -1，错误码为 `EWOULDBLOCK` 或 `EAGAIN`，因此需搭配非阻塞 socket 使用

- 写事件：LT 模式下，不需要写事件一定要及时移除，避免不必要的触发，浪费 CPU 资源；ET 模式下，写事件只会由不可写变成可写时触发，如果需要下一次的写事件触发来驱动任务（例如发上次剩余的数据），可移除可写事件后再注册一次检测可写事件