---
toc:
  enable: true
  number: false
  max_depth: 3
title: Proactor
date: 2023-06-08 20:40:36
tags: 网络编程
categories: 网络编程
---

Proactor 采用了异步 IO 技术，所以被称为异步网络模型

- Reactor 是非阻塞同步网络模式，感知的是就绪可读写事件

- Proactor 是异步网络模式， 感知的是已完成的读写事件

无论是 Reactor 还是 Proactor，都是一种基于事件分发的网络编程模式，区别在于 Reactor 模式是基于待完成的 IO 事件，而 Proactor 模式则是基于已完成的 IO 事件

{% asset_img 01.png %}

Proactor 性能高于 Reactor，但依赖操作系统对异步 IO 的支持