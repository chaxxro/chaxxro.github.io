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
#include <sys/mman.h>
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
// 将修改写入文件，mumap 不保证一定写入
int msync(void *addr, size_t length, int flags);
/*
MS_ASYNC 异步刷新
MS_SYNC 同步刷新
MS_INVALIDATE 使同一文件的其他映射无效，以便可以用刚刚写入的新值更新它们
*/

// 扩展、缩小、移动现有的内存映射
void *mremap(void *old_address, size_t old_size,
             size_t new_size, int flags, ... /* void *new_address */);
/*
默认情况下，如果当前位置没有足够的空间来扩展映射，则 mremap() 会失败
MREMAP_MAYMOVE 允许将映射重新定位到一个新的虚拟地址。如果映射被重新定位，则绝对指针指向旧的映射位置无效
MREMAP_FIXED 
*/
```

大部分的硬件设计都不支持在没有读取权限的情况下执行写操作，所以在 `open` 中应该使用 `O_RDWR` 代替 `O_WRONLY`