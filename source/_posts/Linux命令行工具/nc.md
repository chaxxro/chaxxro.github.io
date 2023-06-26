---
toc:
  enable: true
  number: false
  max_depth: 3
title: nc
date: 2023-04-25 21:18:37
tags: 命令行工具
categories: Linux 命令行
---

用于模拟一个服务器程序被其他客户端接入，或者模拟一个客户端连接其他服务器，连接之后可以发送数据

```sh
nc [-46AcDCdhklnrtUuvz] [-b boundif] [-i interval] [-p source_port]
        [-s source_ip_address] [-w timeout] [-X proxy_protocol]
        [-x proxy_address[:port]] [--apple-delegate-pid pid]
        [--apple-delegate-uuid uuid] [--apple-ext-bk-idle]
        [--apple-nowakefromsleep n] [--apple-ecn mode] [hostname] [port[s]]

# -4 强制使用 IPv4
# -6 强制使用 IPv6
# -A 设置 SO_RECV_ANYIF
# -c 使用 '\r\n' 作为消息结束标志，以 CRLF 作为行结尾，默认使用 '\n' 作为消息的结束标志，
# -i 指定发送与接收间的间隔
# -l 监听模式
# -n 不对任何指定的地址、主机名或端口进行任何 DNS 查找
# -p 指定使用的端口，与 -l 冲突
# -s 指定使用的 ip，与 -l 冲突
# -U 指定使用 unix domain socket
# -u 使用 UDP
# -v 显示详细信息
```

## 客户端、服务器模式

```sh
# 开启一个监听服务，方便客户端连接
nc -v -l 6000

# 模拟客户端
nc -v 127.0.0.1 6000
nc -v -p 5555 0.0.0.0 6000
```

## 数据传输

```sh
nc 0.0.0.0 6000 < file

# 接收文件
nc -l 0.0.0.0 6000 > file
```