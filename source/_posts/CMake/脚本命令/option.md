---
toc:
  enable: true
  number: false
  max_depth: 3
title: option
date: 2023-04-19 13:46:55
tags: cmake
categories: cmake
---

```cmake
option(<variable> "<help_text>" [value])
```

等价于 `set(variable value CACHE BOOL "help_txt")`

提供开关选项，`value` 可取 `on` 和 `off`，默认 `off`

如果 `variable` 已经设置为普通变量或缓存变量，则该命令不执行任何操作
