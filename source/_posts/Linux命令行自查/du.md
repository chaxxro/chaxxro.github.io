---
toc:
  enable: true
  number: false
  max_depth: 3
title: du
date: 2023-03-22 15:21:39
tags: 命令行工具
categories: Linux
---

```sh
du [-Aclnx] [-H | -L | -P] [-g | -h | -k | -m] [-a | -s | -d depth]
        [-B blocksize] [-I mask] [-t threshold] [file ...]
```

disk usage，显示目录或文件的大小

`-a` 为目录中每个文件显示各自磁盘使用情况

`-h` 以 K、M、G 为单位，提高信息的可读性

`-s` 仅显示指定目录总计

`-b` 以 byte 为单位

`-k` 以 kb 为单位

`-m`  以 mb 为单位

`-g`  以 gb 为单位

`-d depth` 指定目录深度

`–exclude=` 略过指定的目录或文件