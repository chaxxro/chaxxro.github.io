---
toc:
  enable: true
  number: false
  max_depth: 3
title: add_library
date: 2023-08-10 21:44:48
tags: cmake
categories: cmake
---

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

默认构建类型取决于 `BUILD_SHARED_LIBS` 的值