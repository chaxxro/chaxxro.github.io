---
toc:
  enable: true
  number: false
  max_depth: 3
title: socketpair
date: 2023-04-26 20:53:19
tags: LinuxApi
categories: LinuxApi
---

`socketpair` 是一对互相连接的 socket，相当于服务端和客户端的两个端点，每个端点都可以读写数据

```cpp
int socketpair(int domain, int type, int protocol, int sv[2]);
```