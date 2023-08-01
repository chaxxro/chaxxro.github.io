---
toc:
  enable: true
  number: false
  max_depth: 3
title: open
date: 2023-07-25 10:17:17
tags: LinuxApi
categories: LinuxApi
---

linux 系统下一切皆文件，而对文件的所有操作都需要打开文件，所有操作结束之后都需要关闭文件，否则会出现预期之外的错误

```cpp
int open (const char* name, int flags);
int open (const char* name, int flags, mode_t mode);
/*
flags 表示文件的访问模式
O_RDONLY、O_WRONLY、O_RDWR 是必选项
以下时可选项
O_APPEND 以追加模式打开
O_ASYNC 当指定的文件可读可写时，会产生一个信号。该标志位只适用于 FIFO、管道、socket 和终端，不适用普通文件
O_CREAT 文件不存在时，内核自动创建
O_SYNC 打开文件用于同步 IO，在数据写到磁盘此前，写操作都不会完成
O_NONBLOCK 非阻塞模式打开
flags 参数取值并非是互斥的，可进行按位或操作

当创建文件时，mode 提供了新建文件的权限
*/
```