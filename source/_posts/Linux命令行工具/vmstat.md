---
toc:
  enable: true
  number: false
  max_depth: 3
title: vmstat
date: 2023-04-25 21:20:12
tags: 命令行工具
categories: Linux 命令行
---

展示给定时间间隔的服务器的状态值

```sh
vmstat T n
# T 采样间隔
# n 采样次数

# r 就绪队列的长度，正在运行和等待 CPU的 进程数
# b 处于不可中断睡眠状态的进程数
# swpd 虚拟内存已使用的大小
# free 空闲的物理内存的大小
# si 每秒从磁盘读入虚拟内存的大小
# so 每秒虚拟内存写入磁盘的大小
# bi 块设备每秒接收的块数量
# bo 块设备每秒发送的块数量
# in 每秒 CPU 的中断次数，包括时间中断
# cs 每秒上下文切换次数
# us 用户 CPU 时间
# sy 系统 CPU 时间
# id 空闲 CPU 时间
# wt 等待 IO 时间
```