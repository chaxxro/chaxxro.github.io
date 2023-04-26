---
toc:
  enable: true
  number: false
  max_depth: 3
title: ftp
date: 2023-04-26 19:42:06
tags: 网络协议
categories: 网络协议
---

FTP 使用 TCP 进行连接，它需要两个连接来传送一个文件

- 控制连接：服务器打开端口号 21 等待客户端的连接，客户端主动建立连接后，使用这个连接将客户端的命令传送给服务器，并传回服务器的应答

- 数据连接：用来传送一个文件数据