---
toc:
  enable: true
  number: false
  max_depth: 3
title: HDFS
date: 2023-08-24 17:58:20
tags: hadoop
categories: 工具自查
---

```sh
# 显示根目录 / 下的文件和子目录，绝对路径
hadoop fs -ls /
# 新建文件夹，绝对路径
hadoop fs -mkdir /hello
# 上传文件
hadoop fs -put hello.txt /hello/
# 下载文件
hadoop fs -get /hello/hello.txt
# 输出文件内容
hadoop fs -cat /hello/hello.txt
# 输出文件内容
hadoop fs -rm /hello/hello.txt
```