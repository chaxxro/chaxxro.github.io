---
toc:
  enable: true
  number: false
  max_depth: 3
title: listen
date: 2023-04-26 20:51:53
tags: LinuxApi
categories: LinuxApi
---

和 `listen()` 相关的大部分信息存储在 `inet_connection_sock` 结构中

在创建套接字的时候使用了 `socket()` 函数，它创建的套接字是主动套接字，`listen()` 函数的功能就是通过这个将主动套接字变成被动套接字，告诉内核应该接受指向这个套接字的请求，CLOSED 状态变成 LISTEN 状态

```cpp
#include <sys/types.h>
#include <sys/socket.h>
int listen(int sockfd, int backlog);
// backlog：已建立连接未 accept 的最大连接数

struct inet_connection_sock {
   /* inet_sock has to be the first member! */
   struct inet_sock      icsk_inet;
   struct request_sock_queue icsk_accept_queue;
   struct inet_bind_bucket   *icsk_bind_hash;
   //....省略后面的代码
}

/*
icsk_accept_queue 规定了内核要为该套接字排队的最大连接个数
*/
```