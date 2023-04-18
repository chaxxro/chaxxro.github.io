---
toc:
  enable: true
  number: false
  max_depth: 3
title: project
date: 2023-04-18 17:49:18
tags: cmake
categories: cmake
---

```cmake
project(<PROJECT-NAME> [<language-name>...])

project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])
```

设置项目的名称，并存储在 `PROJECT_NAME` 中，还会设置 `PROJECT_SOURCE_DIR`、`<PROJECT-NAME>_SOURCE_DIR`、`PROJECT_BINARY_DIR`、`<PROJECT-NAME>_BINARY_DIR`、`PROJECT_IS_TOP_LEVEL`、`<PROJECT-NAME>_IS_TOP_LEVEL`、

当在顶层 CMakeLists.txt 中调用 `project`，名称将同时被存储在 `CMAKE_PROJECT_NAME` 中

`version` 格式 `<major>[.<minor>[.<patch>[.<tweak>]]]`

同时会设置以下变量：

- `PROJECT_VERSION`，`<PROJECT-NAME>_VERSION`

- `PROJECT_VERSION_MAJOR`，`<PROJECT-NAME>_VERSION_MAJOR`

- `PROJECT_VERSION_MINOR`，`<PROJECT-NAME>_VERSION_MINOR`

- `PROJECT_VERSION_PATCH`，`<PROJECT-NAME>_VERSION_PATCH`

- `PROJECT_VERSION_TWEAK`，`<PROJECT-NAME>_VERSION_TWEAK`

当在顶层 CMakeLists.txt 中调用 `project`，同时会设置 `CMAKE_PROJECT_VERSION`

用 `project-description-string` 设置 `PROJECT_DESCRIPTION`、`<PROJECT-NAME>_DESCRIPTION`

当在顶层 CMakeLists.txt 中调用 `project`，同时会设置 `CMAKE_PROJECT_DESCRIPTION`

用 `url-string` 设置 `PROJECT_HOMEPAGE_URL`、`<PROJECT-NAME>_HOMEPAGE_URL`

当在顶层 CMakeLists.txt 中调用 `project`，同时会设置 `CMAKE_PROJECT_HOMEPAGE_URL`

`LANGUAGES` 支持 `C`、`CXX`、`CUDA`、`OBJC`、`OBJCXX`、`Fortran`、`HIP`、`ISPC`、`ASM`