---
toc:
  enable: true
  number: false
  max_depth: 3
title: sort
date: 2023-09-27 14:59:14
tags: 命令行工具
categories: Linux 命令行
---

针对文本文件的内容，以行为单位来排序

```sh
sort [-bcCdfghiRMmnrsuVz] [-k field1[,field2]] [-S memsize] [-T dir] [-t char] [-o output] [file ...]

# -c 检查文件是否已经按照顺序排序
# -m 将几个排序好的文件进行合并
# -o 结果存入指定的文件
# -u 输出的结果去重
# -b 忽略每行前面开始出的空格字符
# -d 排序时只处理英文字母、数字及空格字符，忽略其他的字符
# -f 将小写字母视为大写字母
# -i 排序时除了 040 至 176 之间的 ASCII 字符外，忽略其他的字符
# -r 以相反的顺序来排序
# -k field1[,field2]] 按指定的列进行排序
```