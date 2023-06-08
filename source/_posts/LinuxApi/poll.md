---
toc:
  enable: true
  number: false
  max_depth: 3
title: poll
date: 2023-04-26 20:52:10
tags: LinuxApi
categories: LinuxApi
---

`poll` 的功能与 `select` 类似，也是等待一组描述符中的一个成为就绪状态

`poll` 中的描述符只有一个 `pollfd` 数组，数组中的每个元素都表示一个需要监听 IO 操作事件的文件描述符

```cpp
#include <poll.h>
int poll(struct pollfd *fds, unsigned int nfds, int timeout);

struct pollfd {
    int fd;         /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};
/*
合法事件：
POLLIN              有数据可读
POLLRDNORM          有普通数据可读
POLLRDBAND          有优先数据可读
POLLPRI             有紧迫数据可读

POLLOUT             写数据不会导致阻塞
POLLWRNORM          写普通数据不会导致阻塞
POLLWRBAND          写优先数据不会导致阻塞
POLLRDHUB           TCP 连接被对端关闭，或关闭写操作

POLLER              指定的文件描述符发生错误
POLLHUP             指定的文件描述符挂起事件
POLLNVAL            指定的文件描述符非法

POLLIN | POLLPRI 等价于 select() 的读事件
POLLOUT |POLLWRBAND 等价于 select() 的写事件
POLLIN 等价于 POLLRDNORM |POLLRDBAND
POLLOUT 则等价于 POLLWRNORM
*/

// The structure for two events
struct pollfd fds[2];

// Monitor sock1 for input
fds[0].fd = sock1;
fds[0].events = POLLIN;

// Monitor sock2 for output
fds[1].fd = sock2;
fds[1].events = POLLOUT;

// Wait 10 seconds
int ret = poll( &fds, 2, 10000 );
// Check if poll actually succeed
if ( ret == -1 )
    // report error and abort
else if ( ret == 0 )
    // timeout; no event detected
else
{
    // If we detect the event, zero it out so we can reuse the structure
    if ( fds[0].revents & POLLIN )
        fds[0].revents = 0;
        // input event on sock1

    if ( fds[1].revents & POLLOUT )
        fds[1].revents = 0;
        // output event on sock2
}
```

没有最大连接数的限制，原因是它是基于链表来存储的

## select 和 poll 比较

- `select()` 会修改描述符，而 `poll()` 不会，`select()` 之前需要使用 `FD_ZERO()`、`FD_SET()`、`FD_CLR()`、`FD_ISSET()`）

- `select()` 默认只能监听少于 1024 个描述符，如果要监听更多描述符的话，需要修改 `FD_SETSIZE` 之后重新编译，而 `poll()` 没有描述符数量的限制

- `poll()` 提供了更多的事件类型，并且对描述符的重复利用上比 `select()` 高

- 如果一个线程对某个描述符调用了 `select()` 或者 `poll()`，另一个线程关闭了该描述符，会导致调用结果不确定

- `select()` 和 `poll()` 速度都比较慢，每次调用都需要将全部描述符从应用进程缓冲区复制到内核缓冲区，且都需要遍历 fd 来获取就绪的 socket

- 几乎所有的系统都支持 `select()`，但是只有比较新的系统支持 `poll()`

- `select` 的 `timeout` 参数精度为微秒，而 `poll` 和 `epoll` 为毫秒，因此 `select` 更加适用于实时性要求比较高的场景