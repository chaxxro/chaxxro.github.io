---
toc:
  enable: true
  number: false
  max_depth: 3
title: connect
date: 2023-04-26 20:48:24
tags: LinuxApi
categories: LinuxApi
---

客户端通过调用 `connect()`函数来建立与 TCP 服务器的连接

```cpp
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/*
addr：服务器的 socket 地址
addrlen：socket 地址的长度
*/
```

当 `connect` 函数成功返回后，表明 tcp 的三次握手连接已完成，此时 `accept` 函数获取到一个客户端连接并返回

当服务端 syn 队列已满时，新客户端连接的 syn 包会被忽略，但是服务端并不会发送 RST 报文，原因是客户端可以重传 SYN，并期望在超时前未决连接队列找到空位与服务端建立连接

## 返回失败

- 当客户端发送了 SYN 报文后，没有收到确认则返回 `ETIMEDOUT` 错误；失败一次并不会马上返回 `ETIMEDOUT` 错误，没有收到确认就等 6s 后再发一个 SYN 报文，还没有收到就等 24s 再发一个，时间是累加的，如果总共等了 75s 后还是没收到确认，那么客户端将返回  `ETIMEDOUT` 错误

- 客户端连接一个服务器没有侦听的端口，客户端发送了一个 SYN 报文后，然后服务端回复了一个 RST 报文，`connect` 立即返回 `  ECONNREFUSED`

- 客户端调用 `connect` 函数向服务端发送了一个 SYN 报文，这个 SYN 报文在网络传输过程中经过某个路由器时，正好这个路由器出问题了，缺少到达目的地的路由，不能把这个 SYN 报文转发给目的地址，那么该路由器会丢弃这个 SYN 报文，并同时给客户端发送一个主机不可达的 ICMP 差错报文，客户端返回 `EHOSTUNREACH`或 `ENETUNREACH` 错误

## UDP 使用 connect

UDP `connect` 函数的调用，并不会引起和服务器目标端的网络交互，但能够接收对端异步错误的信息

通过对 UDP 套接字进行 `connect` 操作，将 UDP 套接字建立了上下文，该套接字和服务器端的地址和端口产生了联系，正是这种绑定关系给了操作系统内核必要的信息，能够将操作系统内核收到的信息和对应的套接字进行关联

当 `connect` 后调用 `sendto` 或 `send`，操作系统开始尝试往对应的地址和端口发送，当对端不可达时，一个 ICMP 报文会返回给操作系统内核，该 ICMP 报文含有目的地址和端口等信息，从而操作系统可以将错误信息返回给 `recv` 或 `recvfrom`，而不是阻塞

客户端通过 `connect` 绑定服务端的地址和端口，对 UDP 而言，可以有一定程度的性能提升，因为不用每次发送数据时初始化对端地址

## 阻塞和非阻塞模式

- 阻塞模式时，`connect` 会阻塞到连接成功

- 非阻塞模式时，对非阻塞 socket 调用 `connect`，无论连接是否成功都会立即返回；返回 -1，不一定表示连接出错，如果此时错误码是 `EINPROGRESS`，表示正在尝试连接

- 非阻塞模式 `connect` 需要搭配非阻塞的 socket

- 在指定的时间内判断该 socket 是否可写，如果可写说明连接成功，反之则认为连接失败

- 用 `select` 或 `poll` 函数检测其是否可写时，不仅要用 `select` 检测可写，还要使用 `getsockopt` 检测此时 socket 是否出错，通过错误码来检测确定是否连接上，错误码为 0 表示连接上，反之为未连接上