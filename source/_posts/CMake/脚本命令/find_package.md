---
toc:
  enable: true
  number: false
  max_depth: 3
title: find_package
date: 2023-04-18 16:28:57
tags: cmake
categories: cmake
---

`find_package` 有两种非常不一样的模式，分别是 Module mode 和 Config mode

## Module mode

为了方便在项目中引入外部依赖包，cmake 官方预定义了许多寻找依赖包的 Module，存储在 `CMAKE_MODULE_PATH` 中，默认地址是 `path_of_cmake/share/cmake-<version>/Modules` 目录下

每个 Module 以 `Find<PackageName>.cmake` 命名，Cmake 加载 Module 后会自动查找包、检查版本和生成所需信息

## 标准用法

标准用法支持 Module mode 和 Confgi mode，但优先使用 Module mode，如果 Module mode 查找失败会再次以 Config mode 搜索

```cmake
find_package(<PackageName> [version] [EXACT] [QUIET] [MODULE]
             [REQUIRED] [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [NO_POLICY_SCOPE])
```

- `MODULE` 用于表明只使用 Module mode

- `QUIET` 用于禁用消息型信息

- `REQUIRED` 用于表明包必须找到

## 包信息变量

- `<PackageName>_FOUND` 表示包是否找到

- `<PackageName>_INCLUDE_DIRS` 使用包需要包含的头文件

- `<PackageName>_LIBRARIES` 使用包所需要的库文件，是全路径或者链接器能在库搜索目录下找到的库文件名称

- `<PackageName>_DEFINITIONS` 使用包所需要的编译选项

- `<PackageName>_LIBRARY` 库的路径，只有当包提供的是单个库的时候才能使用这形式

- `<PackageName>_INCLUDE_DIR` 使用包所需要包含的头文件目录，只能在单个库的使用，使用者需要将该路径加入到搜索路径中

- `CMAKE_FIND_PACKAGE_NAME`、`<Packagename>_FIND_REQUIRED`、`<PackageName>_FIND_QUIETLY`、`<PackageName>_FIND_VERSION`、`<PackageName>_FIND_VERSION_MAJOR`、`<PackageName>_FIND_VERSION_MINOR`、`<PackageName>_FIND_VERSION_PATCH`、`<PackageName>_FIND_VERSION_TWEAK`、`<PackageName>_FIND_VERSION_COUNT`、`<PackageName>_FIND_VERSION_EXACT`、`<PackageName>_`
