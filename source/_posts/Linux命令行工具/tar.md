---
toc:
  enable: true
  number: false
  max_depth: 3
title: tar
date: 2023-04-25 21:19:50
tags: 命令行工具
categories: Linux 命令行
---

```
tar [-cxtzjvfpPN] target source

c、x、t 只能存在一个
-c: 建立一个压缩文件的参数指令
-x: 解开一个压缩文件的参数指令
-t: 查看 target 里面的文件

-z: 用 gzip 压缩
-j: 用 bzip2 压缩

-v: 压缩的过程中显示文件
-f: 使用档名，在 f 之后要立即接档名

-p: 使用原文件的原来属性
-P: 可以使用绝对路径来压缩
-N: 比后面接的日期(yyyy/mm/dd)还要新的才会被打包进新建的文件中

tar -czvf xxx.tar.gz xxx | split -a 2 -b 200M -d  - xxx.tar.gz
采用管道，其中 - 参数表示将所创建的文件输出到标准输出上

cat xxx.tar.gz.* | tar -zxv
```