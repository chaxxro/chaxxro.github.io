---
toc:
  enable: true
  number: false
  max_depth: 3
title: marco
date: 2023-04-19 15:25:39
tags: cmake
categories: cmake
---

```cmake
macro(<name> [<arg1> ...])
  <commands>
endmacro()
```

```cmake
set(var "ABC")

macro(Moo arg)
    message("arg = ${arg}")  # 输出原值 ABC
    set(arg "abc")
    message("# After change the value of arg.")
    message("arg = ${arg}")  # 输出原值 ABC
endmacro()
```

调用宏时，cmake 会像 c 的预处理一样将宏命令复制到调用处，然后对宏中的 `${xx}` 做字符替换，所以在宏中需要引用参数的话必须写 `${arg}`

因为是直接简单粗暴地替换，所以宏定义中的 `set` 方法试图改变宏定义中传进来的参数 `arg` 是不可能的

|变量|说明
|-|-|
ARGV#|ARGV0 为第一个参数，ARGV1 为第二个参数，依次类推
ARGV|定义宏（函数）时参数为 2 个，实际传了 4 个，则 ARGV 代表实际传入的两个
ARGN|定义宏（函数）时参数为 2 个，实际传了 4 个，则ARGN代表剩下的 2 个
ARGC|实际传入的参数的个数

同理，`ARGN`、`ARGV` 也是字符串的简单替换，因此不能直接使用这些参数，也需要带 `${xx}`

```cmake
# 错误用法
if(ARGV1)
if(DEFINED ARGV2)
if(ARGC GREATER 2)
foreach(var IN LISTS ARGN)

# 正确用法
if(${ARGV1})
if(DEFINED ${ARGV2})
if(${ARGC} GREATER 2)
foreach(var IN LISTS ${ARGN})
```