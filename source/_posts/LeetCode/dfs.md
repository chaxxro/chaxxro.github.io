---
toc:
  enable: true
  number: false
  max_depth: 3
title: dfs
date: 2023-09-14 17:33:29
tags: LeetCode
categories: LeetCode
---

## lc329


[题目](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)

[分析](https://www.bilibili.com/video/BV1mW411d7q8?from=search&seid=5099018830887943293)

## lc332

```cpp
/*
有向图遍历边
1. 每次都贪心地选择最小字节序的结点
2. 遇到死路时，而没有把所有的边都走过一遍的话，就说明这种走法不满足条件，需要沿着树根向上找到最近的一个有其他路可以走的节点把新的路走一遍

题目保证一定存在一条满足要求的条件路径，那么一条这样的死路，一定会相对的在这个节点上存在另一条路，这条路存在一个回到该节点的环

先把这个环走过之后再去走这条死路，就可以保证把以这个节点的所有点都走到
*/
```

[题目](https://leetcode.com/problems/reconstruct-itinerary/)

[分析](https://www.youtube.com/watch?v=4udFSOWQpdg)