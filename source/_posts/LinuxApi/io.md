---
toc:
  enable: true
  number: false
  max_depth: 3
title: io
date: 2023-07-25 10:24:48
tags: LinuxApi
categories: LinuxApi
---

```cpp
// Linux 中最基本的读写函数，可以用于各种数据的读写
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);

/*
read() 函数是负责从 fd 中读取内容
当读成功时，read 返回实际所读的字节数，如果返回的值是 0 表示已经读到文件的结束了，小于 0 表示出现了错误

write() 函数将 buf 中的 n 字节内容写入文件描述符 fd，成功时返回写的字节数，失败时返回 -1

一般来说对于常规文件的读写不会阻塞，函数一定会在有限的时间内返回，但对于网络读取就不一定了，如果网络通信消息一直没有到达则函数剧一直阻塞等待

发送数据的长度超过 socket 缓冲区长度，则返回错误 SOCKET_ERROR
*/
```