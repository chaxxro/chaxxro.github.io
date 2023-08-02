---
toc:
  enable: true
  number: false
  max_depth: 3
title: sendfile
date: 2023-08-01 21:40:14
tags: LinuxApi
categories: LinuxApi
---

`sendfile` 将 `mmap` + `write` 合二为一，实现了一样效果的同时还简化了用户接口

```cpp
 #include <sys/sendfile.h>
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);

/*
1. out_fd 和 in_fd 分别代表了写入和读出的文件描述符
2. in_fd 必须是一个指向文件的文件描述符，且要能支持类 mmap() 内存映射，不能是 Socket 类型
3. out_fd 可以是任意类型的文件描述符
4. offset 是一个代表了 in_fd 偏移量的指针，指示该从 in_fd 的哪个位置开始读取
5. count 参数是此次调用需要传输的字节总数
6. 返回值是实际复制数据的长度 
7. 函数返回后，offset 会被更新成最后读取的字节位置处，表明此次调用共读取了多少文件数据

*/
```

数据读写流程：

1. 调用 `sendfile` 时用户态陷入内核态

2. DMA 将数据从硬盘拷贝到内核缓冲区

3. CPU 将内核缓冲区拷贝到 socket 缓冲区

4. DMA 将 socket 缓冲区拷贝到网卡完成数据传输

5. `snedfile` 返回，上下文切换到用户态