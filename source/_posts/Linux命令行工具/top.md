---
toc:
  enable: true
  number: false
  max_depth: 3
title: top
date: 2023-03-21 10:08:42
tags: 命令行工具
categories: Linux 命令行
---

`top` 能够实时显示系统中各个进程的资源占用状况

## 命令行模式

```
top [-a | -d | -e | -c mode]
         [-F | -f]
         [-h]
         [-i interval]
         [-l samples]
         [-ncols columns]
         [-o key | -O skey]
         [-R | -r]
         [-S]
         [-s delay-secs]
         [-n nprocs]
         [-stats keys]
         [-pid processid]
         [-user username]
         [-U username]
         [-u]

```

`-i interval` 指定刷新时间

`-pid id` 显示指定的进程信息

`-o +/-key` 按照 key 排序，正负号表示正反序，支持 pid、command、cpu、time、threads、ports、mem、pgrp、ppid、uid

`-user user`、`-U user` 指定用户

## 交互模式

- `m` 切换显示内存信息模式

- `t` 切换显示进程和 CPU 状态信息模型

- `P` 按 CPU 使用率排行

- `M` 按 MEM 排行

- `1` 显示各 CPU 情况

- `q` 退出程序

- `k` 终止一个进程

- `c` 切换显示命令名称和完整命令行

## 显示信息

{% asset_img 01.png %}

第一行：当前系统时间、系统已运行时间、当前登入用户、系统 1 分钟、5 分钟 15 分钟的负载情况，假设机器的 cpu 核心数为 n，则当负载的平均值为 n 的时候，机器就是刚好满负载运行了，如果大于 n，就是超负荷运行了

第二行：当前系统进程情况

第三行：用户空间占用 CPU 的百分比、内核空间占用 CPU 的百分比、改变过优先级的进程占用 CPU 的百分比、空闲 CPU 百分比、IO 等待占用 CPU 的百分比、硬中断（Hardware IRQ）占用 CPU 的百分比、软中断（Software Interrupts）占用 CPU 的百分比

第四行：物理内存总量、空闲内存总量、使用中的内存总量、缓存的内存量

第五行：交换区总量、空闲交换区总量、使用的交换区总量

{% asset_img 02.png %}

PID：进程id

USER：进程所有者

PR：进程优先级

NI：负值表示高优先级，正值表示低优先级

VIRT：进程使用的虚拟内存总量，只要是进程申请过的内存，即便还没有真正分配物理内存，也会计算在内

RES：进程实际使用的物理内存大小，但不包括 Swap 和共享内存

SHR：共享内存大小，比如与其他进程共同使用的共享内存、加载的动态链接库以及程序的代码段等

S：进程状态，D 不可中断的睡眠状态，R 运行，S 睡眠，T 跟踪/停止，Z 僵尸进程

%CPU：上次更新到现在的CPU时间占用百分比

%MEM：进程使用的物理内存百分比
