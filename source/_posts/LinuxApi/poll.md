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

`poll` 的功能与 `select` 类似，也是等待一组描述符中的一个成为就绪状态，但通过底层使用链表解决了 `select` 连接数限制的问题

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

int svr_fd = get_svr_fd(10000);

std::vector<pollfd> fds{pollfd()};
fds.back().fd = svr_fd;
fds.back().events = POLLIN;

while (1) {
  int ret = poll(fds.data(), fds.size(), 10000);
  if (ret == -1) {
    // 错误
  } else if (ret == 0) {
    // 超时
  } else {
    for (auto &fd : fds) {
      if (fd.revents & POLLIN) {
        fd.revents = 0;
        if (fd.fd == svr_fd) {
          int cli = accept_cli(svr_fd);
          send_msg(cli);
          fds.push_back(pollfd());
          fds.back().fd = cli;
          fds.back().events = POLLIN;
        } else {
          recv_msg(fd.fd);
        }
      }
    }
  }
}
```

## select 和 poll 比较

- `select()` 会修改描述符，而 `poll()` 不会，`select()` 之前需要使用 `FD_ZERO()`、`FD_SET()`、`FD_CLR()`、`FD_ISSET()`）

- `select()` 默认只能监听少于 1024 个描述符，如果要监听更多描述符的话，需要修改 `FD_SETSIZE` 之后重新编译，而 `poll()` 没有描述符数量的限制

- `poll()` 提供了更多的事件类型，并且对描述符的重复利用上比 `select()` 高

- 如果一个线程对某个描述符调用了 `select()` 或者 `poll()`，另一个线程关闭了该描述符，会导致调用结果不确定

- `select()` 和 `poll()` 速度都比较慢，每次调用都需要将全部描述符从应用进程缓冲区复制到内核缓冲区，且都需要遍历 fd 来获取就绪的 socket

- 几乎所有的系统都支持 `select()`，但是只有比较新的系统支持 `poll()`

- `select` 的 `timeout` 参数精度为微秒，而 `poll` 和 `epoll` 为毫秒，因此 `select` 更加适用于实时性要求比较高的场景