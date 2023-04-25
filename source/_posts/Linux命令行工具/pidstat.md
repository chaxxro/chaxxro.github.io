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

```sh
pidstat [options] [interval] [times]

# -u 默认参数，显示各个进程的 CPU 统计信息
# -r 显示各个进程的内存使用情况
# -d 显示各个进程的 IO 使用
# -w 显示各个进程的上下文切换
# -p PID 指定 PID

# cswch 每秒自愿上下文切换次数 （进程无法获取所需资源导致的上下文切换）
# 每秒非自愿上下文切换次数 （时间片轮流等系统强制调度）
```