---
toc:
  enable: true
  number: false
  max_depth: 3
title: target_include_directories
date: 2023-04-18 19:21:15
tags: cmake
categories: cmake
---

```cmake
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

`AFTER` 向后追加，`BEFORE` 向前追加

包含目录可以是绝对地址，也可以是相对地址，其中相对地址会被自动转换为以当前 CMakeLists.txt 所在目录为基目录的绝对地址