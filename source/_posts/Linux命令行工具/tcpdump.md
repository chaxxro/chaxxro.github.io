---
toc:
  enable: true
  number: false
  max_depth: 3
title: tcpdump
date: 2023-04-25 21:19:57
tags: 命令行工具
categories: Linux 命令行
---

抓包工具

```sh
-i    指定抓包网卡名

-X    以 ASCII 和十六进制形式输出抓包数据，减去链路层的包头信息

-XX   以 ASCII 和十六进制形式输出抓包数据，显示链路层的包头信息

-n    不显示 IP 地址别名

-nn   不显示 IP 地址和端口别名

-S    以绝对值显示包的 ISN 包序列号，默认以上一包的偏移量显示

-vv   显示详细的抓包数据

-w    将抓包数据写入文件
```