---
toc:
  enable: true
  number: false
  max_depth: 3
title: accept
date: 2023-04-26 20:47:26
tags: LinuxApi
categories: LinuxApi
---

如果 `accept()` 成功返回，则服务器与客户已经正确建立连接了，此时服务器通过返回的套接字来完成与客户的通信

```cpp
#include <sys/types.h>
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/*
第一个参数为 socket 创建的监听套接字，返回的是已连接套接字

addr 用来接受一个返回值，这返回值指定客户端的地址

addrlen 用来接受 addr 的结构的大小的，它指明 addr 结构所占有的字节个数

如果第二三个参数为空，代表了对客户的身份不感兴趣，因此置为 NULL
*/
```

`accept()` 默认会阻塞进程，直到有一个客户连接建立后返回，它返回的是一个新可用的套接字，这个套接字是连接套接字，该套接字是阻塞模式的

## accept4

```cpp
int accept4(int sockfd, struct sockaddr* addr, socklen_t addrlen, int flags)
/*
flags
0，就跟 accept() 一样
SOCK_NONBLOCK 为新打开的文件描述符设置 O_NONBLOCK 标志位，这跟用 fcntl() 设置的效果是一样的
SOCK_CLOEXEC 为新打开的文件描述符设置 FD_CLOEXEC 标志位，使用 fcntl() 设置 FD_CLOEXEC 标志位，open() 的时候设置的 O_CLOEXEC 也能达到同样的效果
*/
```

## 非阻塞模式

当 socket 是非阻塞时，无论连接队列中是否有需要处理的连接，`accept` 都会立即返回，不会阻塞

如果有连接，则 `accept` 返回一个大于 0 的值，这个返回值即是 clientfd

如果没有连接，`accept` 返回值小于 0，错误码 errno 为 `EWOULDBLOCK` 或 `EAGAIN`