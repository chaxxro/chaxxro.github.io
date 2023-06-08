---
toc:
  enable: true
  number: false
  max_depth: 3
title: link_directories
date: 2023-06-08 21:22:05
tags: cmake
categories: cmake
---

```cmake
link_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
```

将 dir 放入搜索库文件地址列表 `LINK_DIRECTORIES` 中，插入位置默认是末尾 `AFTER`