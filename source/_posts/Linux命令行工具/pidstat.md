---
toc:
  enable: true
  number: false
  max_depth: 3
title: pidstat
date: 2023-04-25 21:18:55
tags: 命令行工具
categories: Linux 命令行
---

进程性能分析工具，用来实时查看进程的 CPU、内存、I/O 以及上下文切换等性能指标

```sh
pidstat [options] [interval] [times]

-u 默认参数，显示各个进程的 CPU 统计信息
-r 显示各个进程的内存使用情况
-d 显示各个进程的 IO 使用
-w 显示各个进程的上下文切换，一个 cswch 自愿上下文切换，一个 nvcswch 非自愿上下文切换
-p PID 指定 PID
-t 查看线程相关的信息，默认只显示进程数据
```