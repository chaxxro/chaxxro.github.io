---
toc:
  enable: true
  number: false
  max_depth: 3
title: msgxx
date: 2023-05-31 21:18:00
tags: LinuxApi
categories: LinuxApi
---

消息队列

```cpp
// key：用来指定返回 MQ 的 ID
// msgflg：创建的标志
// return：成功返回队列 ID，失败返回 -1, 并设置 erron
int msgget(key_t key, int msgflg);

/*
 * msgid：消息队列 ID
 * msgp：指向 msgbuf 的指针，用来指定发送的消息
 * msgsz：要发送消息的长度
 * msgflg：创建标记，如果指定 IPC_NOWAIT，失败会立刻返回
 * return：成功返回 0, 失败返回 -1, 并设置 erron
 */
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

/*
 * msgid：消息队列 ID
 * msgp：指向 msgbuf 的指针，用来接收消息
 * msgsz：要接收消息的长度
 * msgtyp：接收消息的方式
 * msgflg：创建标记，如果指定 IPC_NOWAIT，获取失败会立刻返回
 * return：成功返回实际读取消息的字节数, 失败返回 -1, 并设置 erron
 */
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

/*
 * msqid：消息队列 ID
 * cmd：控制命令，例如 IPC_RMID 删除命令
 * buf：存储消息队列的相关信息的 buf
 * return：成功根据不同的 cmd 有不同的返回值，失败返回 -1, 并设置 erron
 */
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```