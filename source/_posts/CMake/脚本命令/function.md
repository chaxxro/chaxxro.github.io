---
toc:
  enable: true
  number: false
  max_depth: 3
title: function
date: 2023-04-19 14:50:32
tags: cmake
categories: cmake
---

cmake 函数名不区分大小写

```cmake
function(<name> [<arg1> ...])
  <commands>
endfunction()
```

一个函数将新建一个作用域

|变量|说明
|-|-|
ARGV#|ARGV0 为第一个参数，ARGV1 为第二个参数，依次类推
ARGV|定义宏（函数）时参数为 2 个，实际传了 4 个，则 ARGV 代表实际传入的两个
ARGN|定义宏（函数）时参数为 2 个，实际传了 4 个，则ARGN代表剩下的 2 个
ARGC|实际传入的参数的个数

```cmake
set(var "ABC")

function(Foo arg)
    message("arg = ${arg}")  # 输出原值 ABC
    set(arg "abc")
    message("# After change the value of arg.")  # 输出修改后的值 abc
    message("arg = ${arg}")
endfunction()

message("=== Call function ===")
Foo(${var})
```

通过 `Foo(${var})` 调用函数时，CMake 会将变量进行展开，依次匹配函数声明中的参数列表，相当于传统函数调用中的值传递

在 `function` 中定义的变量，变量仅在函数内和函数调用中可见

`CMAKE_CURRENT_FUNCTION` 当前函数名称

`CMAKE_CURRENT_FUNCTION_LIST_DIR` 当前函数路径

`CMAKE_CURRENT_FUNCTION_LIST_FILE` 当前函数所属文件

`CMAKE_CURRENT_FUNCTION_LIST_LINE` 当前函数定义的起始行数