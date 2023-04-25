---
toc:
  enable: true
  number: false
  max_depth: 3
title: lsof
date: 2023-04-25 21:18:31
tags: 命令行工具
categories: Linux 命令行
---

列出当前系统打开的文件描述符

```
# 显示当前系统打开的文件
lsof 

# 仅查看某个用户打开的文件信息
lsof -u username

# 仅列出所有 tcp 网络连接
lsof -i tcp

# 仅列出所有 udp 网络连接
lsof -i udp

# 列出端口号
lsof -i:port

# 显示 abc 进程现在打开的文件
lsof -c abc

# 通过某个进程号显示该进行打开的文件
lsof -p pid

# 设置显示进程名字符数
lsof +c 15 # 设置进程名最多显示 15 个字符

# 强制显示 IP 地址而不是别名
lsof -n

# 强制显示端口号而不是别名
lsof -P
```
