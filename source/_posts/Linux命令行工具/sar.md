---
toc:
  enable: true
  number: false
  max_depth: 3
title: sar
date: 2024-01-09 16:57:14
tags: 命令行工具
categories: Linux 命令行
---

对系统当前的状态进行取样，然后通过计算数据和比例来表达系统的当前运行状态

```sh
sar [options] t n

t 采样间隔
n 采样次数

-A 显示所有报告信息
-u CPU 利用率
-q 平均负载
-n { keyword [,...] | ALL } 网络统计信息，支持 DEV、EDEV、NFS、NFSD、SOCK、IP、EIP、ICMPEICMP、TCPETCP、UDP、SOCK6、IP6、EIP6、ICMP6、EICMP6、UDP6
DEV 网络接口信息
IFACE 本地网卡名
rxpck/s 和 txpck/s 分别表示每秒接收、发送的网络帧数
rxkB/s 和 txkB/s 分别表示每秒接收、发送的千字节数

EDEV 网络错误信息
IFACE 本地网卡名
rxerr/s 和 txerr/s 分别表示每秒接收、发送的错误数
rxdrop/s 和 txdrop/s 分别表示每秒因缓冲区满而丢弃的包数

SOCK 套接字信息
totsck socket 总数
tcpsck tcp socket 总数
udpsck udp socket 总数
tcp-tw TIME-WAIT 连接数

-d 设备使用信息
-r 内存统计信息
-v inode、文件等内核表
-B 内存分页信息
-b IO 和传送速率信息
-f 从指定文件提取报告
```