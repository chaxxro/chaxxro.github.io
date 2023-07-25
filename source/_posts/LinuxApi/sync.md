---
toc:
  enable: true
  number: false
  max_depth: 3
title: sync
date: 2023-07-25 21:02:47
tags: LinuxApi
categories: LinuxApi
---

同步磁盘的系统调用函数

```cpp
void sync(void);
int fsync(int fildes);
int fdatasync(int fd);
```

- `sync` 一次将内核缓冲区中的数据全部写入磁盘，linux 系统下该函数是同步函数，即所有脏页回写磁盘后才会返回

- `fsync` 将 fd 对应的内核缓冲区中的脏页刷盘，并且会写元数据，元数据包括文件修改的时间戳以及 inode 中的其他属性

- `fdatasync` 只会回写文件的数据及文件大小，文件的其他元数据不会被更新

就性能而言，`fdatasync`` > `fsync`` >> `sync`