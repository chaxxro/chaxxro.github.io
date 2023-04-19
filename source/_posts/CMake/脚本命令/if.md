---
toc:
  enable: true
  number: false
  max_depth: 3
title: if
date: 2023-04-18 21:22:10
tags: cmake
categories: cmake
---

```cmake
if(<condition>)
  <commands>
elseif(<condition>)
  <commands>
else()
  <commands>
endif()
```

- `if(<constant>)`：当 `constant` 为 `TRUE` 、1、`ON`、`YES`、`Y` 和非 0 数时都为 `true`，当 `constant` 为 `FALSE`、`0`、`OFF`、`NO`、`N`、`IGNORE`、`NOTFOUND`、空字符串和以 `-NOTFOUND` 结尾的字符串时都为 `false`

- `if(<variable>)`：如果变量被定义且不被定义为 `false` 的常量时为 `true`，宏参数、环境变量不能以这种方式进行判断

- `if(<string>)`：用引号括起来的字符串的计算结果总是为 `false`，除非字符串是为 `true` 的常量

- `if(NOT <condition>)`

- `if(<cond1> AND <cond2>)`

- `if(<cond1> OR <cond2>)`

- `if((condition) AND (condition OR (condition)))`

- `if(COMMAND command-name)`：当 `command-name` 是可以被调用的命令、宏和函数时为 `true`

- `if(TARGET target-name)`：当 `target-name` 已经被 `add_executable`、`add_library` 和 `add_custom_target` 添加时为 `true`

- `if(DEFINED <name>|CACHE{<name>}|ENV{<name>})`：当变量、环境变量、全局变量已被定义时为 `true`，不关系其具体的值

- `if(<variable|string> IN_LIST <variable>)`

- `if(EXISTS path-to-file-or-directory)`：只适用于绝对地址

- `if(file1 IS_NEWER_THAN file2)`

- `if(IS_DIRECTORY path-to-directory)`

- `if(IS_ABSOLUTE path)`：空串为 `false`，

- `if(<variable|string> MATCHES regex)`

- `if(<variable|string> LESS <variable|string>)`：`variable|string` 必须是数字

- `if(<variable|string> GREATER <variable|string>)`

- `if(<variable|string> EQUAL <variable|string>)`

- `if(<variable|string> LESS_EQUAL <variable|string>)`

- `if(<variable|string> GREATER_EQUAL <variable|string>)`

- `if(<variable|string> STRLESS <variable|string>)`

- `if(<variable|string> STRGREATER <variable|string>)`

- `if(<variable|string> STREQUAL <variable|string>)`

- `if(<variable|string> STRLESS_EQUAL <variable|string>)`

- `if(<variable|string> STRGREATER_EQUAL <variable|string>)`

- `if(<variable|string> VERSION_LESS <variable|string>)`

- `if(<variable|string> VERSION_GREATER <variable|string>)`

- `if(<variable|string> VERSION_EQUAL <variable|string>)`

- `if(<variable|string> VERSION_LESS_EQUAL <variable|string>)`

- `if(<variable|string> VERSION_GREATER_EQUAL <variable|string>)`

```cmake
if(var)
# 等价于
if(${var})

set(var1 OFF)
set(var2 "var1")
if(var1) # var1 被定义成 false 常量 -> false
if(var2) # var2 被定义，且不是 false 常量 -> true
if(${var1}) # 等价于 if(OFF) -> false
if(${var2}) # 等价于 if(var1) -> false
```