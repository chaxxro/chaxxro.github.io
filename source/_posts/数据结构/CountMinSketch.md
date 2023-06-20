---
toc:
  enable: true
  number: false
  max_depth: 3
title: CoundMinSketch
date: 2023-06-19 21:32:36
tags: 数据结构
categories: 数据结构
---

当需要在一定准确性情况下统计元素的个数，可以使用 CountMinSketch 数据结构

CountMinSketch 通过牺牲部分准确性来支持固定空间

CountMinSketch 有 d 个哈希函数和 d 个长度为 n 的数组，其工作流程：

1. 每个哈希函数对应一个数组，数组的初始值都是 0

2. 插入元素时，计算元素的 d 个对应哈希值，并将相对应数组中的值加 1

2. 元素次数是各个数组中相对应位置的最小值

应用场景：大数据量且对计数的准确性要求不高