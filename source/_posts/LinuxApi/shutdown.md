---
toc:
  enable: true
  number: false
  max_depth: 3
title: shutdown
date: 2023-04-26 21:12:39
tags: LinuxApi
categories: LinuxApi
---
# ()

```cpp
int shutdown(int sockfd, int how);

/*
how 取值：

SHUT_RD(0)：关闭 sockfd 上的读功能，此选项将不允许 sockfd 进行读操作；该套接字不再接受数据，任何当前在套接字接受缓冲区的数据将被丢弃；如果再有新的数据流到达，会对数据进行 ACK，然后悄悄地丢弃

SHUT_WR(1)：关闭 sockfd 的写功能，此选项将不允许 sockfd 进行写操作，即进程不能在对此套接字发出写操作；套接字上发送缓冲区已有的数据将被立即发送出去，并发送一个 FIN 报文给对端

SHUT_RDWR(2)：关闭 sockfd 的读写功能，相当于调用 shutdown 两次，首先 SHUT_RD 然后 SHUT_WR

成功则返回 0，错误返回 -1
错误码 errno：EBADF 表示 sockfd 不是一个有效描述符；ENOTCONN 表示 sockfd 未连接
*/
```

`shutdown()` 的效果是累计的，不可逆转的。既如果关闭了一个方向数据传输，那么这个方向将会被关闭直至完全被关闭或删除，而不能重新被打开

`shutdown` 函数并不会要求操作系统底层回收套接字等资源，真正会回收资源是 `close` 函数