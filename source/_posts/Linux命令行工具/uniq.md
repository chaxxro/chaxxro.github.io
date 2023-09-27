---
toc:
  enable: true
  number: false
  max_depth: 3
title: uniq
date: 2023-09-27 14:46:38
tags: 命令行工具
categories: Linux 命令行
---

用于检查及删除文本文件中重复出现的相邻行列，一般与 `sort`` 命令结合使用

```sh
uniq [-c | -d | -D | -u] [-i] [-f num] [-s chars] [input_file
          [output_file]]

# -c 显示该行重复出现的次数
# -d 仅显示重复出现的行列
# -u 仅显示不重复的行列
# -i 忽略大小写
# -s 忽略 chars 开头的行
# -f num, --skip-fields num 忽略前几位字符

# 假设文件内容
Madrid
Lisbon
Madrid

uniq -u cities.txt
Madrid
Lisbon
Madrid

sort cities.txt | uniq -c
1 Lisbon
2 Madrid
```