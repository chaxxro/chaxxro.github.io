---
toc:
  enable: true
  number: false
  max_depth: 3
title: read
date: 2023-04-25 20:32:27
tags: 命令行工具
categories: Linux 命令行
---

从标准输入读取数值

```sh
read [-ers] [-a aname] [-d delim] [-i text] [-n nchars] [-N nchars] [-p prompt] [-t timeout] [-u fd] [name ...]

-n 指定读取字符
-d 指定结束符，默认按行读取
-p 指定提示信息，即在输入前打印提示信息
-t 指定等待时间
```


