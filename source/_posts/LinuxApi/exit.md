---
toc:
  enable: true
  number: false
  max_depth: 3
title: exit
date: 2023-05-31 21:16:32
tags: LinuxApi
categories: LinuxApi
---

立即终止调用进程，任何属于该进程的打开的文件描述符都会被关闭，该进程的子进程由进程 1 继承

```cpp
void exit(int status)
// status -- 返回给父进程的状态值
```