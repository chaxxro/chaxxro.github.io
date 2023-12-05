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

```sh
perf stat [-e <EVENT> | --event=EVENT] [-a] <command>
perf stat [-e <EVENT> | --event=EVENT] [-a] — <command> [<options>]

-e, --event <event> 指定事件
--filter <filter> 过滤事件
-i 不统计子进程
-a 对全部 CPU 进行计数
-p 指定进程
-t 指定线程
-v 详细信息
-I 指定事件间隔，单位毫秒，最小 100ms
-r 重复运行，并显示平均信息
```

## 采样

`perf record` 和 `perf top` 对系统进行剖析

### perf top

`perf top` 可以看到目前的 CPU 执行占比情况，该情况会随着时间刷新，这可以帮助快速的发现热点

```sh
perf top [-e <EVENT> | --event=EVENT] [<options>]

-a 全系统采样
-c 每采样 n 个事件记录一次
-d 刷新间隔时间
-e, --event <event> 指定事件
-p 指定进程
-t 指定线程
```

{% asset_img 01.png %}

- Overhead 该符号的性能事件在所有采样事件中的比例

- Shared 该函数或指令所在的动态共享对象，如内核、进程名、动态链接库

- Object 动态共享对象类型，`.` 表示用户空间的可执行程序，`k` 内核空间

- Symbol 符号名、函数名，函数名未知时用十六进制表示

### perf record

`perf record` 是把多个时间的 `perf top` 结果作为切片保存到一个文件里，从而得到一段时间里的执行情况，默认在当前目录下生成数据文件 perf.data

```sh
perf record [-e <EVENT> | --event=EVENT] [-l] [-a] <command>
perf record [-e <EVENT> | --event=EVENT] [-l] [-a] —- <command> [<options>]

-e, --event <event> 指定事件
--filter <filter> 过滤事件
-a 对全部 CPU 进行计数
-p 指定进程
-t 指定线程
-f 覆盖已存在的数据文件
-c 每采样 n 个事件记录一次
-o 输出文件名
-g 保存调用栈
-s 每个线程都统计
-F, --freq <n> 采样频率
```

`perf record` 得到的结果数据是无法直接读取的，可以用 `perf script` 将其转换成可读文件，或者直接用 `perf report` 进行图形化展示