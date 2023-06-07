---
toc:
  enable: true
  number: false
  max_depth: 3
title: find_library
date: 2023-06-07 11:12:39
tags: cmake
categories: cmake
---

`find_library` 是一个用于在系统中搜索特定的库文件，它不依赖于库提供的 CMake 配置文件，而是直接查找库文件

使用 `find_library` 时，需要手动指定库文件路径、头文件路径等

```cmake
find_library (<VAR> name1 [path1 path2 ...])

find_library (
          <VAR>
          name | NAMES name1 [name2 ...] [NAMES_PER_DIR]
          [HINTS [path | ENV var]... ]
          [PATHS [path | ENV var]... ]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC "cache documentation string"]
          [NO_CACHE]
          [REQUIRED]
          [NO_DEFAULT_PATH]
          [NO_PACKAGE_ROOT_PATH]
          [NO_CMAKE_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [CMAKE_FIND_ROOT_PATH_BOTH |
           ONLY_CMAKE_FIND_ROOT_PATH |
           NO_CMAKE_FIND_ROOT_PATH]
         )
```

- `NAMES` 指定库名

- `HINTS, PATHS` 指定额外的搜索地址，`ENV var` 指定从环境变量读取

- `NO_CACHE` 将结果存储在普通变量的 `VAR` 中，而不是 cache 变量 `VAR`