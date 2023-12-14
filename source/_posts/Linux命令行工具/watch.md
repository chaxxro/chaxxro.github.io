---
toc:
  enable: true
  number: false
  max_depth: 3
title: watch
date: 2023-12-13 17:08:18
tags: 命令行工具
categories: Linux 命令行
---

定期执行程序，展示输出

```sh
watch [options] command
-d 高亮显示变化的区域
-n 刷新间隔

watch -d ls -l
watch -d 'ls -l | fgrep joe'
```