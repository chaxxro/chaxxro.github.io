---
toc:
  enable: true
  number: false
  max_depth: 3
title: mpstat
date: 2023-12-13 14:10:44
tags: 命令行工具
categories: Linux 命令行
---

多核 CPU 性能分析工具，用来实时查看每个 CPU 的性能指标，以及所有 CPU 的平均指标

```sh
mpstat [ -A ] [ -n ] [ -u ] [ -V ] [ -I { keyword [,...] | ALL } ] [ -N { node_list | ALL } ] [ -o JSON ] [ -P { cpu_list | ALL } ] [ interval [ count ] ]

-P 指定 CPU 列表，格式 0,2,4-7,12-


# 显示结果
%user 用户态的 CPU 时间
%nice nice 值为负进程的 CPU 时间
%sys 内核时间
%iowait 硬盘 IO 等待时间
%irq 硬中断时间
%soft 软中断时间
%idle 除去等待磁盘 IO 操作外的因为任何原因而空闲的时间闲置时间
```