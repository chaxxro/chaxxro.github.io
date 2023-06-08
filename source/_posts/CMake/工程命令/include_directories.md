---
toc:
  enable: true
  number: false
  max_depth: 3
title: include_direcotries
date: 2023-06-08 21:21:55
tags: cmake
categories: cmake
---

```cmake
include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
```

将 dir 放入搜索头文件地址列表 `INCLUDE_DIRECTORIES` 中，插入位置默认是末尾 `AFTER`