---
toc:
  enable: true
  number: false
  max_depth: 3
title: net_io
date: 2023-06-01 16:22:11
tags: LinuxApi
categories: LinuxApi
---

## TCP 常用接口

```cpp
// 只用于 socket 的数据处理
#include <sys/types.h>
#include <sys/socket.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);

/*
flags 可以指定发送带外数据，即紧急数据
MSG_OOB(0x01)：不接受外带数据，某些协议将加速数据放置在普通数据队列的开头，因此该标志不能用于此类协议

MSG_PEEK(0x02)：从接收数据的开头返回数据，且不删除数据，因此，后续的调用将返回相同的数据

MSG_TRUNC(0x20)：返回数据包或数据报的实际长度，即使比传递的缓冲区长

MSG_DONTWAIT(0x40)：启用非阻塞操作

MSG_WAITALL(0x100)：请求块操作，未读取请求数目字节之前不返回
*/

/*
send() 原理：
1. send() 只负责将数据提交给协议层
2. send() 先比较待发送数据的长度 count 和套接字 fd 的发送缓存的长度
3. 如果 count 大于 fd 的发送缓存的长度，该函数返回 SOCKET_ERROR
4. 如果 count 小于或者等于 fd 的发送缓存的长度，那么 send() 先检查协议是否正在发送发送缓存中的数据
5. 如果正在发送数据，则等待数据发送完
6. 如果协议没有在发送 fd 发送缓冲中的数据或者 fd 的发送缓冲中没有数据，那么 send() 就比较 fd 的发送缓冲区的剩余空间和 count
7. 如果 count 大于剩余空间大小，send() 就一直等待协议把 fd 的发送缓冲中的数据发送完，如果 count 小于剩余空间大小，send() 就仅仅把 buf 中的数据 copy 到剩余空间里

recv() 原理：
1. recv() 仅仅是 copy 数据，真正的接收数据是协议来完成的
1. recv() 先检查套接字 fd 的接收缓冲区，如果 fd 接收缓冲区中没有数据或者协议正在接收数据，那么 recv() 就一直等待，直到协议把数据接收完毕
2. 当协议把数据接收完毕，recv() 就把 fd 的接收缓冲中的数据 copy 到 buf 中
3. 协议接收到的数据可能大于 buf 的长度，所以在这种情况下要调用几次 recv() 才能把 fd 的接收缓冲中的数据 copy 完

recv() 返回值
-1：发送时报错
0：对端关闭连接
>0：接受数据长度
*/

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);

/*
同时将缓冲区的数据读到多个缓冲区中和同时将多个缓冲区数据写入内核缓冲区
*/
ssize_t readv(int fd, const struct iovec* iov, int iovcnt);
ssize_t writev(int fd, const struct iovec* iov, int iovcnt);
ssize_t preadv(int fd, const struct iovec* iov, int iovcnt, off_t offset);
ssize_t pwritev(int fd, const struct iovec* iov, int iovcnt, off_t offset);

struct iovec {
    void    *iov_base;      /* starting address of buffer */
    size_t  iov_len;        /* size of buffer */
}

struct msghdr {
    void * msg_name;  /* protocol address */
    socklen_t msg_namelen;   /* sieze of protocol address */
    struct iovec * msg_iov;  /* scatter/gather array */
    int msg_iovlen;  /* # elements in msg_iov */
    void * msg_control;  /* ancillary data ( cmsghdr struct) */
    socklen_t msg_controllen;  /* length of ancillary data */
    int msg_flags;  /* flags returned by recvmsg() */
}
/*
msg_name, msg_namelen 用于未连接的套接字（主要是UDP），用来指定接受来源或发送目的地址，对于已连接的套接字课直接设置为 NULL 和 0

msg_iov, msg_iovlen 用于指定数据缓冲区数组，即 iovec 结构数组，缓冲区是个二维数组，每一维长度不是固定的，需要提前设置好这两项并且分配好内存
如果只是当存传送一个字符串，那只需要将 msg_iovlen 设置成1，然后将数据赋给 iov[0].iov_base 就行了

msg_control, msg_controllen 是用来设置辅助数据的位置和大小，可以用来返回关于数据报文的其他指定信息，不过需要通过 setsockopt 函数指定要返回的辅助信息
对于 sendmsg，这两项需要都设置成 0，否则会导致发送数据失败
*/
```

`send` 在本质上并不是向网络发送数据，而是将应用层发送缓冲区的数据拷贝至内核缓冲区，至于数据什么时候从网卡缓冲区中发送到网络中，则是根据 TCP/IP 协议决定的

如果 socket 设置了 `TCP_NODELAY`，存放到内核缓冲区的数据就会被立即发送出去

`recv` 在本质上不是从网络上收取数据，而是将内核缓冲区中的数据拷贝至应用层缓冲区，在拷贝完成后会将内核缓冲区的该部分数据移除

## UDP 常用接口

```cpp
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                struct sockaddr *src_addr, socklen_t *addrlen);

/*
recvfrom 两个参数 from 和 addrlen，实际上是返回对端发送方的地址和端口等信息
sednto 两个参数 to 和 addrlen，表示发送的对端地址和端口等信息
*/
```

- udp 客户端调用 `connect()` 函数：udp 客户端建立了 socket 后可以直接调用 `sendto()` 函数向服务器发送数据，但是需要在 `sendto()` 函数的参数中指定目的地址/端口，但是可以调用 `connect()` 函数先指明目的地址/端口，然后就可以使用 `send()` 函数向目的地址发送数据了，因为此时套接字已经包含目的地址/端口，也就是 `send()` 函数已经知道包含目的地址/端口

- udp 客户端程序使用 `bind()` 函数：udp 服务器调用了 `bind()` 函数为服务器套接字绑定本地地址/端口，这样使得客户端的能知道它发数据的目的地址/端口，服务器如果单单接收客户端的数据，或者先接收客户端的数据(此时通过 `recvfrom()` 函数获取到了客户端的地址信息/端口)再发送数据，客户端的套接字可以不绑定自身的地址/端口，因为 udp 在创建套接字后直接使用 `sendto()`，隐含操作是，在发送数据之前操作系统会为该套接字随机分配一个合适的 udp 端口，将该套接字和本地地址信息绑定。但是，如果服务器程序就绪后一上来就要发送数据给客户端，那么服务器就需要知道客户端的地址信息和端口，那么就不能让客户端的地址信息和端口号由客户端所在操作系统分配，而是要在客户端程序指定了

- 不存在 UDP 发送缓冲区，因为发往 UDP 发送缓冲区的包只要超过一定阈值（值很小）就可以发往对端，所以一般认为 UDP 是没有发送缓冲区的

## socket 缓冲区

每个 socket 被创建后，都会分配两个缓冲区，输入缓冲区和输出缓冲区

`write()/send()` 并不立即向网络中传输数据，而是先将数据写入输出缓冲区中，再由 TCP 协议将数据从缓冲区发送到目标机器。一旦将数据写入到缓冲区，函数就可以成功返回，不管它们有没有到达目标机器，也不管它们何时被发送到网络，这些都是 TCP 协议负责的事情

TCP 协议独立于 `write()/send()` 函数，数据有可能刚被写入缓冲区就发送到网络，也可能在缓冲区中不断积压，多次写入的数据被一次性发送到网络，这取决于当时的网络情况、当前线程是否空闲等诸多因素，不由程序员控制

`read()/recv()` 也类似，从输入缓冲区读取数据，而不是直接从网络中读取

- 使用 `write()/send()` 时：首先会检查缓冲区，如果缓冲区的可用空间长度小于要发送的数据，那么 `write()/send()` 会被阻塞，直到缓冲区中的数据被发送到目标机器，腾出足够的空间，才唤醒 `write()/send()` 函数继续写入数据；如果 TCP 协议正在向网络发送数据，那么输出缓冲区会被锁定，不允许写入，`write()/send()` 也会被阻塞，直到数据发送完毕缓冲区解锁，`write()/send()` 才会被唤醒；如果要写入的数据大于缓冲区的最大长度，那么将分批写入；直到所有数据被写入缓冲区 `write()/send()` 才能返回

- 使用 `read()/recv()` 读取数据时：首先会检查缓冲区，如果缓冲区中有数据，那么就读取，否则函数会被阻塞，直到网络上有数据到来；如果要读取的数据长度小于缓冲区中的数据长度，那么就不能一次性将缓冲区中的所有数据读出，剩余数据将不断积压，直到有 `read()/recv()` 函数再次读取；直到读取到数据后 `read()/recv()` 函数才会返回，否则就一直被阻塞

## 发送方一直 `send`，接收方不 `recv`

- 阻塞模式下，继续调用 `send`，程序会阻塞

- 非阻塞模式下，继续调用 `send` 会立即返回错误 `EAGIN` 或 `EWOULDBLOCK`

## 发送方不 `send`，接收方 `recv`

- 阻塞模式下，接收方阻塞在 `recv`

- 非阻塞模式下，当前无数据可读，`recv` 返回错误码 `EWOULDBLOCK`

## 非阻塞模式下 `send` 和 `recv` 返回值

返回值|含义
|-|-|
大于 0|成功发送、接收 n 字节
0|对端关闭连接，或主动发送 0 字节也会返回 0
小于 0|出错、信号中断、对端 TCP 窗口太小导致数据发送或接收失败

- 返回值大于 0，表示发送或接收多少字节，需要注意的是，在这种情形下，一定要判断下 `send` 函数的返回值是不是我们期望发送的缓冲区长度，而不是简单判断其返回值大于 0

- `send` 函数发送 0 字节数据，协议栈并不会把这些数据发出去

错误码|send|recv
-|-|-|
`EWOULDBLOCK` 或 `EAGAIN`|TCP 窗口太小，数据发送不出去|内核缓冲区无数据可读
`EINTR`|被信号中断，需要重试|被信号中断，需要重试
其他错误码|出错|出错