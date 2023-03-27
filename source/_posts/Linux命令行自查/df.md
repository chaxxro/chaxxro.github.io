---
toc:
  enable: true
  number: false
  max_depth: 3
title: df
date: 2023-03-22 22:29:57
tags: 命令行工具
categories: Linux
---

display free disk space，显示目前系统上的文件系统磁盘使用情况统计

```sh
df [-b | -h | -H | -k | -m | -g | -P] [-ailn] [-t] [-T type]
        [file | filesystem ...]
```

`-a` 显示所有挂载点

`-h` 使用人类可读的格式

`-l` 只显示本地挂载文件系统的信息

`-k` 以 kb 为单位

`-m` 以 mb 为单位

`-g` 以 gb 为单位
