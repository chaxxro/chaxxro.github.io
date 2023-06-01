---
toc:
  enable: true
  number: false
  max_depth: 3
title: perror
date: 2023-05-31 21:19:03
tags: LinuxApi
categories: LinuxApi
---

把一个描述性错误消息输出到标准错误 `stderr`

```cpp
#include <stdio.h>

int perror(const char* e);
```