---
toc:
  enable: true
  number: false
  max_depth: 3
title: configure_file
date: 2023-04-18 19:34:52
tags: cmake
categories: cmake
---

```cmake
configure_file(<input> <output>
               [NO_SOURCE_PERMISSIONS | USE_SOURCE_PERMISSIONS |
                FILE_PERMISSIONS <permissions>...]
               [COPYONLY] [ESCAPE_QUOTES] [@ONLY]
               [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
```

1. 将 input 复制到 output，若使用相对地址，则是相对于 `CMAKE_CURRENT_SOURCE_DIR`

2. 使用 CMakeLists.txt 中的 `VAR` 变量值替换 input 中的 `@VAR@` 和 `${VAR}`，若 `VAR` 在 CMakeLists.txt 中没定义则使用空串替换

3. `#cmakedefine var` 关键字替换成 `#define var` 或者 `/* #undef VAR */`，这取决于 cmake 是否定义了 `var`

4. `#cmakedefine01 var` 关键字替换成 `#define var 0` 或者 `#define var 1`，这取决于 cmake 是否定义了 `var`

- `NO_SOURCE_PERMISSIONS` 不将输入文件的权限转移到输出文件，复制的文件权限默认为标准的644值

- `USE_SOURCE_PERMISSIONS` 将输入文件的权限转移到输出文件，默认行为

- `FILE_PERMISSIONS <permissions>`

- `COPYONLY`

- `@ONLY` 只替换 `@VAR@` 形式变量

- `NEWLINE_STYLE <style>` 指明新文件的换行方式，`UNIX` 或 `LF` 使用 `\n`，`DOS`、`WIN32` 或 `CRLF` 使用 `\r\n`

```cmake
# foo.h.in
#cmakedefine FOO_ENABLE
#cmakedefine FOO_STRING "@FOO_STRING@"

# CMakeLists.txt
option(FOO_ENABLE "Enable Foo" ON)
if(FOO_ENABLE)
  set(FOO_STRING "foo")
endif()
configure_file(foo.h.in foo.h @ONLY)

# 替换后
#define FOO_ENABLE
#define FOO_STRING "foo"
```