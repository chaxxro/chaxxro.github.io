---
toc:
  enable: true
  number: false
  max_depth: 3
title: mmap
date: 2023-07-25 21:44:48
tags: LinuxApi
categories: LinuxApi
---

```cpp
void *mmap(void *addr, size_t length, int prot, int flags,
           int fd, off_t offset);
/*
addr 指定内核映射文件的最佳位置，一般情况下传 0

length fd 指向的字节数

prot 指定访问权限，访问权限不可与 fd 打开的访问模式冲突
PROT_READ 页可读
PROT_WRITE 页可写
PROT_EXEC 页可执行

flags 指定其他操作行为
MAP_PRIVATE 表示映射区不共享，文件映射采用了写时复制，进程对内存的任何改变不影响真正文件或其他进程的映射
MAP_SHARED 表示和所有其他映射该文件的进程共享映射内存，对内存的写操作等效于写文件

offset 映射起点与文件头的偏移
*/

// 取消映射
int munmap(void *addr, size_t length);
```
