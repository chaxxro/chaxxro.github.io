---
toc:
  enable: true
  number: false
  max_depth: 3
title: tr
date: 2023-09-27 11:48:49
tags: 命令行工具
categories: Linux 命令行
---

对输入的字符进行替换、压缩和删除

```sh
tr [OPTION]... SET1 [SET2]
# -c 反选设定字符，符合 SET1 的部份不做处理
# -d 删除所有属于第一字符集的字符
# -s 把连续重复的字符以单独一个字符表示
# -t 删除第一字符集较第二字符集多出的字符

# SET1 指定要转换或删除的原字符集
# SET2 指定要转换成的目标字符集

# 字符集支持
# 1. 字符
# 2. 转义
# 3. c1-c2 以 ASCII 码的次序从 c1 到 c2，只能由小到大
# 4. [:class:] 分类，支持 alnum 字母字符与数字、alpha 字母字符、blank 水平空格、cntrl 控制字符、digit 数字、graph 可打印的字符(不包含空格符)、lower 小写字母、print 可打印的字符(包含空格符)、punct 标点字符、space 水平与垂直空格符、upper 大写字母、xdigit 16 进位制的数字
# 5. \octal 八进制

# 一个字符一行
tr -cs "[:alpha:]" "\n" < file1
# 小写转大写
tr "[:lower:]" "[:upper:]" < file1
# 删除所有不可打印字符
tr -cd "[:print:]" < file1
# 压缩字符
echo "thissss is      a text linnnnnnne." | tr -s ' sn'
this is a text line.
```
