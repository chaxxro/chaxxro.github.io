---
toc:
  enable: true
  number: false
  max_depth: 3
title: truncate
date: 2023-12-21 11:01:59
tags: LinuxApi
categories: LinuxApi
---

将文件设置为指定的大小

```cpp
#include <unistd.h>
#include <sys/types.h>

int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
```