---
toc:
  enable: true
  number: false
  max_depth: 3
title: gdb
date: 2023-04-01 15:38:58
tags: gdb
categories: 工具自查
---

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v{1,2,3,4,5};
    for(int a : v) {
        cout<<a<<endl;
    }
    return 0;
}

// 为 g++ 添加 -g 选项
// g++ -g main.

// 运行程序 gdb a.out
```

## 启动 GDB

- 启动程序并调试，`gdb [program]`

- 调试 core 文件，`gdb [program] [core]`

- 通过 pid 调试已运行的程序，`gdb [program] [pid]`

## 启动参数

`gdb program` 时为 `main` 函数添加启动参数

```
gdb program
# 方式 1
r hello
# 方式 2
set args hello
r
```

## 脚本参数设置

```
set pagination off # 全部输出，中间不会暂停
set logging on # 打开日志模式，将调试信息输出至日志中
set print pretty on
set print object on
set print static-members on
set print vtbl on
set print demangle on
set demangle-style gnu-v3
set print sevenbit-strings off
```

## 命令

### run

运行程序，可简写 `r`

### list

查看程序代码

```
# 展开指定行号附近代码
list [file:]linenum
# 展开指定函数附近代码
list [file:]function
```

### break

在指定文件函数打断点，可简写 `b`

```
# 指定函数入口打断点
b [file:]function if expr
# 指定行号打断点
b [file:]linenum if expr

# 当前行的前几行或后几行设置断点
b +OFFSET
b -OFFSET
```

### tbreak

简写 `tb`，添加临时断点

### watch

对变量设置观察点，当变量值变化时展示新旧值

```
watch var
```

### condition

```
condition bnum exp
```

对断点添加条件表达，或修改条件表达

### backtrace

简写 `bt`，打印当前栈

### print

按表达式打印值，可简写 `p`

```
p expr

p {var1, var2, var3}
```

配合 `@` 可以查看一段连续的内存空间，`p *arr@len`

### ptype

查看变量类型

### continue

简写 `c`，继续执行程序

### next

单步执行，跳过函数调用，等价于 F10，可简写 `n`

### step

单步执行，可简写 `s`

### until

简写 `u`，运行到指定行停止

### finish

简写 `fi`，结束当前函数，返回上一层函数调用处

### return

结束当前函数，并指定返回值

### jump

简写 `j`，跳转到制定行或地址

### info

查看相关信息

```
# 查看断点
info breakpoints
# 查看线程
info thread
# 查看当前函数参数
info args
# 查看当前局部变量
info lolcals
# 查看全局变量和静态变量
info variables
# 查看内存映射进程空间信息
info proc m
# 查看寄存器
info registers
```

### disassemble

查看汇编

### disable、enable

禁用、启用断点

```
# bp num 可从 info 得到
disable bpnum
enable bpnum
```

### delete

删除断点

```
# bp num 可从 info 得到
delete bpnum
```

### quit

结束调试，可简写 `q`

### set

设置别名

```
# 别名一定要是 $ 开头
set $a=*ctx
p $a.search_id_
```

## shell

```
# 在 gdb 中可执行 shell 命令
shell command
```

## core 文件

当打开生成 core 文件后，程序奔溃会生成 core 文件

```
gdb a.out core
```

## 技巧

可以将内存地址按照它指向对象的真实类型进行转型然后输出

```
set $c =*(guodong::CommKvInfo*)0x7fef48c93df0
p $c
```

## gdbinit

https://gist.github.com/apetresc/436804

该 .gdbinit 中提供了几个函数来打印 STL 容器

`pvector`、`plist`、`pmap`、`pset`、`dequeue`、`pstack`、`pqueue`、`pqueue`、`pbitset`、`pstring`

这份 .gdbinit 不支持 `std::unordered_map`，可以使用 gdb 自带的 `printers.py`

```sh
# 1. 先找到 printers.py
find / -name "printers.py" 2> /dev/null
# 输出 /usr/share/gcc-4.8.2/python/libstdcxx/v6/printers.py

# 2. 在 .gdbinit 中引入 printers.py
python
import sys 
sys.path.insert(0, '/usr/share/gcc-4.8.2/python')
from libstdcxx.v6.printers import register_libstdcxx_printers
register_libstdcxx_printers (None)
end
```