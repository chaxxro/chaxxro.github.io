---
toc:
  enable: true
  number: false
  max_depth: 3
title: target_compile_definitions
date: 2023-04-18 19:08:41
tags: cmake
categories: cmake
---

```cmake
target_compile_definitions(<target>
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

`target` 不能是 alias target

```cmake
add_compile_definitions(target MACRO_FEATURE_A)
# 等同于 add_compile_options(target -DMACRO_FEATURE_A)

# 定义会被自动移除头部的 -D
target_compile_definitions(foo PUBLIC FOO)
target_compile_definitions(foo PUBLIC -DFOO)  # -D removed
target_compile_definitions(foo PUBLIC "" FOO) # "" ignored
target_compile_definitions(foo PUBLIC -D FOO) # -D becomes "", then ignored

target_compile_definitions(foo PUBLIC FOO=1)
```
