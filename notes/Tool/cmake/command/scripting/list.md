# list

同 `set` 一样，使用 `list` 修改夫 CMakeLists.txt 中的列表时会产生新的列表

## 创建

使用 `set` 可以创建列表

```cmake
set(var a b c d e)
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