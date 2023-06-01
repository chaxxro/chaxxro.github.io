---
toc:
  enable: true
  number: false
  max_depth: 3
title: get_current_dir_name
date: 2023-06-01 15:49:18
tags:
categories:
---

```cpp
#include <unistd.h>

// 当 buf 是空时，getcwd 会调用 malloc
char *getcwd(char *buf, size_t size);

// 该函数不会使用 malloc 函数动态的分配内存
// 但是返回值参数 buf 的大小至少是 PATH_MAX
char *getwd(char *buf);

// 函数内部调用 malloc
char *get_current_dir_name(void);
```