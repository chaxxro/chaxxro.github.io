---
toc:
  enable: true
  number: false
  max_depth: 3
title: perf
date: 2023-06-19 11:16:41
tags: 命令行工具
categories: Linux 命令行
---

perf 是 performance 的缩写，是一个事件驱动的可观测性工具

## 事件

`perf list` 查看支持事件，一般来说分为六类

- 硬件事件，来自于 CPU 硬件监控计数器

- 软件事件，来自于内核计数器

- 内核追踪点事件，来自于内核中硬编码的静态指令点

- USDT 事件，来自于用户程序的静态追踪点

- 动态追踪事件，来自于软件动态插桩

- 时许剖析，来自于通过 `perf record` 收集到的数据

### 软件事件

- cpu-clock，cpu 执行的计数器

- task-clock，某个任务在 cpu 上运行时的 clock 数

- page-faults，缺页中断数

- alignment-faults，对齐错误

- context-switches，上下文切换数

- cpu-migrations，任务在 cpu 间迁移数

- minor-faults，缺页中断一部分，指的是访问在内存中但是没有映射到程序地址空间的页发生的错误

- major-faults，缺页中断一部分，指的是访问不在内存中的页，需要磁盘参与进行换页的中断

### 硬件事件

- cache-misses，缓存不命中

- branch-misses，分支预测失败

- cpu-cycles，cpu 时钟情况

- stalled_cycles_frontend，cpu 前端的停滞周期数

- stalled_cycles_backend，cpu 后端的停滞周期数

## 计数

`perf stat` 来收集一些计数信息

## 采样剖析

`perf record` 和 `perf top` 对系统进行剖析

执行 `perf top` 可以看到目前的 CPU 执行占比情况，该情况会随着时间刷新，这可以帮助快速的发现热点

`perf record` 则像是把多个时间的 `perf top` 结果作为切片保存到一个文件里，从而得到一段时间里的执行情况

`perf record` 得到的结果数据是无法直接读取的，可以用 `perf script` 将其转换成可读文件，或者直接用 `perf report` 进行图形化展示