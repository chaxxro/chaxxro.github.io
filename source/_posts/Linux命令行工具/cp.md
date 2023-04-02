---
toc:
  enable: true
  number: false
  max_depth: 3
title: cp
date: 2023-03-22 11:42:17
tags: 命令行工具
categories: Linux 命令行
---

```sh
cp [-R [-H | -L | -P]] [-fi | -n] [-alpsvXx] source_file target_file
cp [-R [-H | -L | -P]] [-fi | -n] [-alpsvXx] source_file ... target_directory
```

`-l` 对源文件建立硬连接，而非复制文件

`-s`对源文件建立符号连接，而非复制文件；

`-n` 复制时不覆盖已存在文件

`-f` 强行复制文件或目录，不论目标文件或目录是否已存在

`-i` 覆盖既有文件之前先询问用户

`-p` 保留源文件或目录的属性

`-R` 递归处理，将指定目录下的所有文件与子目录一并处理

`-d`当复制符号连接时，把目标文件或目录也建立为符号连接，并指向与源文件或目录连接的原始文件或目录；