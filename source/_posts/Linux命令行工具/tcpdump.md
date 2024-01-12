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

tcpdump 会读取网络中的数据，解析协议，然后与表达式相匹配，如果能匹配上则用指定的方式输出数据包的内容

```sh
tcpdump [ -AbdDefhHIJKlLnNOpqRStuUvxX ] [ -B buffer_size ] [ -c count ]
        [ -C file_size ] [ -G rotate_seconds ] [ -F file ]
        [ -i interface ] [ -j tstamp_type ] [ -m module ] [ -M secret ]
        [ -P in|out|inout ]
        [ -r file ] [ -V file ] [ -s snaplen ] [ -T type ] [ -w file ]
        [ -W filecount ]
        [ -E spi@ipaddr algo:secret,...  ]
        [ -y datalinktype ] [ -z postrotate-command ] [ -Z user ]
        [ expression ]

-i    指定抓包网卡名
-A    用 ASCII 输出数据包内容
-X    以 ASCII 和十六进制形式输出抓包数据，不包括链路层的包头信息
-XX   以 ASCII 和十六进制形式输出抓包数据，包括链路层的包头信息
-n    不显示 IP 地址别名
-nn   不显示 IP 地址和端口别名
-S    以绝对值显示包的 ISN 包序列号，默认以上一包的偏移量显示
-v -vv -vvv   显示详细的抓包数据
-w    将抓包数据写入文件

表达式告诉 tcpdump 抓取哪些报文，它由一个或多个基本表达式组成，支持用 &&、||
基本表达式的格式为一个或多个修饰词 + ID，修饰词是预定义的关键字
类型修饰词表示 ID 所指的类型. 它可以是 host、net、port、portrange 等，如 host localhost、net 128.3、port 20、portrange 6000-6008
方向修饰词指定数据传输的方向，可以是 src 或 dst
协议修饰词指定协议，可以是 tcp、udp、ip、ip6、arp、ether 等

TCP 报文
08:41:13.729687 IP 192.168.64.28.22 > 192.168.64.1.41916: Flags [P.], seq 196:568, ack 1, win 309, options [nop,nop,TS val 117964079 ecr 816509256], length 372
Flags 支持 S-SYN、F-FIN、P-PUSH、R-RST、.-ACK

```