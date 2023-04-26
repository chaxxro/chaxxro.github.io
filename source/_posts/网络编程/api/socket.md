---
toc:
  enable: true
  number: false
  max_depth: 3
title: socket
date: 2023-04-26 20:53:10
tags: 网络编程
categories: LinuxApi
---

`socket()` 用于创建一个 socket 描述符，它唯一标识一个 socket

```cpp
#include <sys/types.h>
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
/*
domain: 协议域，其决定了 socket 的地址类型

type: 指定socket类型

protocol: 指定协议，为 0 时会自动选择 type 类型对应的默认协议

type 和 protocol 不可以随意组合的
*/
```

`AF_` 表示的含义是 Address Family

domain|说明|
-|-|
AF_INET|IPv4
AF_INET6|IPv6
AF_LOCAL|Unix 域协议，用于本地通信，也可以写成 AF_FILE、AF_UNIX
AF_ROUTE|路由套接字
AF_KEY|秘钥套接字

type|说明|
-|-|
SOCK_STREAM|字节流套接字
SOCK_DGRAM|数据包套接字
SOCK_SEQPACKET|有序分组套接字
SOCK_RAW|原始套接字
SOCK_NONBLOCK|非阻塞

protocol|说明|
-|-|
IPPROTO_TCP|TCP
IPPROTO_UDP|UDP
IPPROTO_SCTP|SCIP
IPPROTO_TIPC|TIPC