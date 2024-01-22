---
toc:
  enable: true
  number: false
  max_depth: 3
title: Linux 内存性能
date: 2024-01-19 14:33:20
tags: 操作系统
categories: Linux性能
---

`free` 会显示 buffer 和 cache 的总和

## buffer

buffer 是内核缓冲区用到的内存，对应的是 `/proc/meminfo` 中的 buffers 值

buffer 是对原始磁盘块的临时存储，既可以用作将要写入磁盘数据的缓存，也可以用作从磁盘读取数据的缓存

## cache

cache 是内核页缓存和 Slab 用到的内存，对应的是 `/proc/meminfo` 中的 cached 与 SReclaimable 之和

cache 是从磁盘读取文件的页缓存，既可以用作从文件读取数据的页缓存，也可以用作写文件的页缓存