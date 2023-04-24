---
toc:
  enable: true
  number: false
  max_depth: 3
title: include
date: 2023-04-19 14:04:49
tags: cmake
categories: cmake
---

用来载入并运行来自于文件或模块的 cmake 代码

```cmake
include(<file|module> [OPTIONAL] [RESULT_VARIABLE <var>]
                      [NO_POLICY_SCOPE])
```

- `OPTIONAL` 找不到文件不报错

- `RESULT_VARIABLE` 将完整文件名存储在 `var` 中，如果没找到则设置为 `NOTFOUND`

- `module` 命名格式是 `<modulename>.cmake`，加载时先去 `CMAKE_MODULE_PATH` 中搜索，然后再去 CMake module 目录中搜索

`include()` 不会引入新的变量作用域，因此被加载的文件可以直接修改调用方的普通变量

`include()` 也不会改变 `CMAKE_CURRENT_SOURCE_DIR` 和 `CMAKE_CURRENT_BINARY_DIR` 