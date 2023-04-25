---
toc:
  enable: true
  number: false
  max_depth: 3
title: sysctl
date: 2023-04-25 21:19:43
tags: 命令行工具
categories: Linux 命令行
---

`sysctl` 命令被用于在内核运行时动态地修改内核的运行参数，可用的内核参数在目录 /proc/sys 中

使用 `sysctl` 修改系统变量，也可以通过编辑 sysctl.conf 文件来修改系统变量

`sysctl` 变量的设置通常是字符串、数字或者布尔型，布尔型用 1 来表示 yes，用 0 来表示 no

```sh
sysctl [opt] [var=val]

# opt 选项
# -n：打印值时不打印关键字
# -e：忽略未知关键字错误
# -N：仅打印名称
# -w：当改变 sysctl 设置时使用此项
# -p：从配置文件 /etc/sysctl.conf 加载内核参数设置
# -a：打印当前所有可用的内核参数变量和值
# -A：以表格方式打印当前所有可用的内核参数变量和值

# 常用变量
# 保活时间
net.ipv4.tcp_keepalive_time 
# 保活时间间隔
net.ipv4.tcp_keepalive_intvl、
# 保活探测次数
net.ipv4.tcp_keepalve_probes
# TIME_WAIT 的连接阈值
net.ipv4.tcp_max_tw_buckets
# listen blacklog 默认值
net.ipv4.tcp_max_syn_backlog
```