---
toc:
  enable: true
  number: false
  max_depth: 3
title: FetchContent
date: 2023-04-19 19:31:30
tags: cmake
categories: cmake
---

```cmake
# 引入模块
include(FetchContent)
```

使用 `FetchContent` 的步骤总结起来就是：

- 使用 `FetchContent_Declare(Name)` 获取项目，可以是一个 URL 也可以是一个 Git 仓库

- 使用 `FetchContent_MakeAvailabe(name1 ...)` 引入依赖

## FetchContent_Declare

声明依赖

```cmake
FetchContent_Declare(
  <name>
  <contentOptions>...
  [OVERRIDE_FIND_PACKAGE |
   FIND_PACKAGE_ARGS args...]
)

# 支持 option
# GIT_REPOSITORY GIT_TAG URL URL_HASH SVN_REPOSITORY SVN_REVISION

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)
```

## FetchContent_MakeAvailable

构建依赖

```cmake
FetchContent_MakeAvailable(<name1> [<name2>...])
```