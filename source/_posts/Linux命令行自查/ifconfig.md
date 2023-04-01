---
toc:
  enable: true
  number: false
  max_depth: 3
title: ifconfig
date: 2023-03-20 15:21:07
tags: 命令行工具
categories: Linux 命令行
---

`ifconfig` 用于查看和设置网络信息

## 查看网络信息

默认显示当前激活的网卡列表，以及每个网卡的 IPv4 地址、IPv6 地址、子网掩码、广播地址等

`-s` 显示精简列表

`-a` 显示所有网卡，包括未激活网卡

{% asset_img 01.jpg %}

- eth0 表示第一块网卡

- flags 表示网卡状态

- MTU 表示最大传输单元

- inet 表示网卡 IP 地址

- netmask 表示网络掩码

- broadcast 表示广播地址

- inet6、prefixlen、scopeid 表示 IPv6 信息

- ether 表示连接类型

- 52:54:00:0e:57:a9 表示 mac 地址

- txqueuelen 表示网卡设置的传输队列长度

- RX 系列分别接受的正确数据包数、接受的数据量、接受时产生错误的数据包数、接受时丢弃的数据包数、接受时由于速度过快而丢失的数据包数、接受时发生 frame 错误丢失的数据包数

- TX 系列分别发送的正确数据包数、发送的数据量、发送时产生错误的数据包数、发送时丢弃的数据包数、发送时由于速度过快而丢失的数据包数、发送时发生 carrier 错误丢失的数据包数

## 设置网络信息

```sh
# 启动网卡
ifconfig eth0 up
# 关闭网卡
ifconfig eth0 down
# 配置 ip 地址、子网掩码和广播地址
ifconfig eth0 192.168.1.100 netmask 255.255.255.0 broadcast 192.168.1.255
# 启用 arp
ifconfig eth0 arp
# 禁用 arp
ifconfig eth0 -arp
# 修改 mtu
ifconfig eth0 mtu 1500
```