---
toc:
  enable: true
  number: false
  max_depth: 3
title: strerror
date: 2023-05-31 21:16:09
tags: LinuxApi
categories: LinuxApi
---

变量 `errno` 存放一个正整数来表明上一个系统调用的错误值，仅当系统调用发生错误时才设置它

对于线程而言，每个线程都有专用的 `errno` 变量，它不是一个共享的变量，因此不必考虑多线程同步问题

```cpp
#include <errno.h>
// errno 记录系统的最后一次错误代码，是个 int 型

#include <string.h>
char *strerror(int errnum);
```

- 当错误码是 `EINTR` 时，表明被信号中断，需要再次调用函数进行重试
