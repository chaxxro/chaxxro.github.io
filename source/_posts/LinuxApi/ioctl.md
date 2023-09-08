---
toc:
  enable: true
  number: false
  max_depth: 3
title: ioctl
date: 2023-04-26 20:51:46
tags: LinuxApi
categories: LinuxApi
---
 
当一个非监听 socket 可读时，使用 `ioctl` 可以获取接受缓冲区已有多少数据可读

```cpp
int ioctl(int d, int request, ...)
```