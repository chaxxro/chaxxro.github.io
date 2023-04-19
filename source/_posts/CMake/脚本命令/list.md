---
toc:
  enable: true
  number: false
  max_depth: 3
title: list
date: 2023-04-19 17:35:57
tags: cmake
categories: cmake
---

列表也是字符串，这个变量有多个值，每个值用分号 `;` 进行分隔

引用列表不加引号时，cmake 将自动在分号处进行切分成多个列表元素，并把它们作为多个独立的参数传给命令

引用列表加了引号时，cmake 不会进行切分并保持分号不动，整个引号内的内容当作一个参数传给命令

```cmake
set(list_var 1 2 3 4) # list_var = 1;2;3;4
set(list_foo "5;6;7;8") # list_foo = 5;6;7;8
message(${list_var})#输出： 1234
message(${list_foo})#输出：5678
message("${list_var}")#输出：1;2;3;4
message("${list_foo}")#输出：5;6;7;8
```

## 读

```cmake
list(LENGTH <list> <out-var>)
list(GET <list> <element index> [<index> ...] <out-var>)
list(JOIN <list> <glue> <out-var>)
list(SUBLIST <list> <begin> <length> <out-var>)
```

`GET` 获取部分元素存储在结果列表中

`JOIN` 将列表元素以 `glue` 拼接成字符串

## 查找

```cmake
list(FIND <list> <value> <out-var>)
```

返回索引

## 修改

```cmake
list(APPEND <list> [<element>...])
list(FILTER <list> {INCLUDE | EXCLUDE} REGEX <regex>)
list(INSERT <list> <index> [<element>...])
list(POP_BACK <list> [<out-var>...])
list(POP_FRONT <list> [<out-var>...])
list(PREPEND <list> [<element>...])
list(REMOVE_ITEM <list> <value>...)
list(REMOVE_AT <list> <index>...)
list(REMOVE_DUPLICATES <list>)
list(TRANSFORM <list> <ACTION> [...])
```

当前作用域没有 `list`变量时，`APPEND`、`INSERT`、`PREPEND` 会创建新的列表 

## 排序

```cmake
list(REVERSE <list>)
list(SORT <list> [...])
```