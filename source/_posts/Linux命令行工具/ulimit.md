---
toc:
  enable: true
  number: false
  max_depth: 3
title: ulimit
date: 2023-04-25 21:20:04
tags: 命令行工具
categories: Linux 命令行
---

资源限制

```
ulimit -a: 查看所有限制
# data seg size 程序的数据段限制
# scheduling priority 优先级限制
# file size 文件大小限制
# pending signals 未决信号个数限制
# max locked memory 最大可以锁内存的空间限制
# max memory size 最大物理内存使用限制
# open files 文件打开个数限制
# pipe size 管道空间限制
# real-time priority 实时优先级限制
# stack size 程序栈空间限制
# cpu time 占用 CPU 时间限制
# max user processes 可以打开的的进程个数限制
# virtual memory 虚拟内存空间限制
```