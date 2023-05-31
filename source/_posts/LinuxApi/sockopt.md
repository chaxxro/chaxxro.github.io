---
toc:
  enable: true
  number: false
  max_depth: 3
title: sockopt
date: 2023-04-26 20:49:53
tags: LinuxApi
categories: LinuxApi
---

```cpp
int setsockopt(int sock, int level, int optname, 
               const void *optval, socklen_t optlen);
int getsockopt(int sock, int level, int optname, 
               void *optval, socklen_t *optlen);

/*
sock：将要被设置或者获取选项的套接字
level：选项所在的协议层
optname：需要访问的选项名
optval：对于 getsockopt()，指向返回选项值的缓冲。
        对于 setsockopt()，指向包含新选项值的缓冲。
optlen：optval 长度

成功执行时，返回 0，失败返回 -1，errno 被设为以下的某个值  
EBADF：sock 不是有效的文件描述词
EFAULT：optval 指向的内存并非有效的进程空间
EINVAL：在调用 setsockopt() 时，optlen 无效
ENOPROTOOPT：指定的协议层不能识别选项
ENOTSOCK：sock 不是套接字

level 指定协议层，可以取三种值
SOL_SOCKET：通用套接字选项
IPPROTO_IP：IP 选项.
IPPROTO_TCP：TCP 选项

SOL_SOCKET 对应 optname
SO_BROADCAST，允许发送广播数据
SO_DEBUG，允许调试
SO_DONTROUTE，不查找路由
SO_ERROR，获得套接字错误
SO_KEEPALIVE，保持连接
SO_LINGER，延迟关闭连接
SO_OOBINLINE，带外数据放入正常数据流
SO_RCVBUF，接收缓冲区大小
SO_SNDBUF，发送缓冲区大小
SO_RCVLOWAT，接收缓冲区下限
SO_SNDLOWAT，发送缓冲区下限
SO_RCVTIMEO，接收超时
SO_SNDTIMEO，发送超时
SO_REUSERADDR，允许重用本地地址和端口
SO_TYPE，获得套接字类型
SO_BSDCOMPAT，与 BSD 系统兼容

IPPROTO_IP 对应 optname
IP_HDRINCL，在数据包中包含IP首部
IP_OPTINOS，IP 首部选项
IP_TOS，服务类型
IP_TTL，生存时间

IPPRO_TCP 对应 optname
TCP_MAXSEG，TCP 最大数据段的大小
TCP_NODELAY，不使用 Nagle 算法

/*
SO_LINGER 设置 close 或 shutdown 的行为
对应 optval 为 linger

1. 如果 l_onoff 为 0，那么关闭本选项，l_linger 的值被忽略，对应了默认行为，close 或 shutdown 立即返回。如果在套接字发送缓冲区中有数据残留，系统会将试着把这些数据发送出去

2. 如果 l_onoff 为非 0， 且 l_linger 值也为 0，那么调用 close 后，会立该发送一个 RST 标志给对端，该 TCP 连接将跳过四次挥手，也就跳过了 TIME_WAIT 状态，直接关闭。这种关闭的方式称为强行关闭，在这种情况下，排队数据不会被发送，被动关闭方也不知道对端已经彻底断开。只有当被动关闭方正阻塞在 recv() 调用上时，接受到 RST 时，会立刻得到一个 connet reset by peer 的异常

3. 如果 l_onoff 为非 0， 且 l_linger 的值也非 0，那么调用 close 后，调用 close 的线程就将阻塞，直到数据被发送出去，或者设置的 l_linger 计时时间到
*/
struct linger {
　int　 l_onoff;　　　　/* 0=off, nonzero=on */
　int　 l_linger;　　　　/* linger time, POSIX specifies units as seconds */
}

/* 
SO_RCVBUF 设置接受缓冲区
1. 当设置 TCP 套接口接收缓冲区的大小时，函数调用顺序是很重要的，因为 TCP 的窗口规模选项是在建立连接时用 SYN 与对方互换得到的

2. 对于客户端，`O_RCVBUF` 选项必须在 `connect` 之前设置

3. 对于服务端，`SO_RCVBUF` 选项必须在 `listen` 前设置
*/
int nRecvBuf = 32*1024;  // 设置为 32K
setsockopt(s, SOL_SOCKET, SO_RCVBUF,
           (const char*)&nRecvBuf, sizeof(int));


/*
TCP_NODELAY 关闭 Naggle 优化
*/
int on = 1;
setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (void *)&on, sizeof(on));


/*
SO_REUSEADDR 复用 TIME_WAIT 连接

本机服务器如果有多个地址，还可以在不同地址上使用相同的端口提供服务

服务器端程序，都应该设置 SO_REUSEADDR 套接字选项，以便服务端程序可以在极短时间内复用同一个端口启动
*/
int on = 1;
setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

/*
SO_RCVTIMEO 设置 recv 阻塞超时时常

出错信息是 EAGAIN 或者 EWOULDBLOCK
*/
struct timeval tv;
tv.tv_sec = 5;
tv.tv_usec = 0;
setsockopt(connfd, SOL_SOCKET, SO_RCVTIMEO, 
           (const char *) &tv, sizeof tv);
```

