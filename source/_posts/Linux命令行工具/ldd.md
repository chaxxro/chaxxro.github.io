---
toc:
  enable: true
  number: false
  max_depth: 3
title: ldd
date: 2023-12-26 16:46:54
tags: 命令行工具
categories: Linux 命令行
---

打印依赖的动态库

```sh
ldd [option]... file...

-v 打印所有信息
-u 打印不直接依赖的库
```

在比较老的 glibc 版本（2.2 或更早），ldd 可能会显示一个目录下的动态库，但是真正运行时可能链接另一个目录的动态库。该问题在 glibc 2.3.2 版本上修复了