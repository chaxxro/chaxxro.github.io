---
toc:
  enable: true
  number: false
  max_depth: 3
title: cmake_minimum_required
date: 2023-04-18 16:23:56
tags: cmake
categories: cmake
---

```cmake
cmake_minimum_required(VERSION <min>[...<policy_max>] [FATAL_ERROR])
```

`cmake_minimum_required` 将会设置 `CMAKE_MINIMUM_REQUIRED_VERSION`

`cmake_minimum_required` 需要在顶层 CMakeLists.txt 中，并且在 `project` 前