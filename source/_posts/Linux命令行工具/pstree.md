---
toc:
  enable: true
  number: false
  max_depth: 3
title: pstree
date: 2023-12-25 21:27:10
tags: 命令行工具
categories: Linux 命令行
---

用树状形式显示所有进程之间的关系

```sh
 pstree [-a, --arguments] [-c, --compact] [-h, --highlight-all, -Hpid, --highlight-pid pid] [-g] --show-pgids] [-l, --long] [-n, --numeric-sort]
       [-N, --ns-sortns [-p, --show-pids] [-s, --show-parents] [-S, --ns-changes] [-t, --thread-names] [-T, --hide-threads] [-u, --uid-changes] [-Z, --secu‐
       rity-context] [-A, --ascii, -G, --vt100, -U, --unicode] [pid, user]

-a：显示所有进程的命令行参数
-c：显示进程的真实名称，而不是简短的命令名称
-h：高亮当前进程和父进程
-l：显示进程的完整命令行参数
-n：按 pid 排序
-p：显示进程的父进程
```