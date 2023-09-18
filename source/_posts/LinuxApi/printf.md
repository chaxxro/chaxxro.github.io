---
toc:
  enable: true
  number: false
  max_depth: 3
title: printf
date: 2023-05-31 21:19:26
tags: LinuxApi
categories: LinuxApi
---

```cpp
int printf ( const char * format, ... );
```

发送格式化输出到标准输出 `stdout`

`format` 标签属性是 `%[flags][width][.precision][length]specifier`

specifier|说明|
-|-|
d|以十进制形式输出带符号整数
o|以八进制形式输出无符号整数，
x,X|以十六进制形式输出无符号整数，不输出前缀 0
u|以十进制形式输出无符号整数，不输出前缀 `Ox`
f|以小数形式输出单、双精度实数
c|输出单个字符
s|输出字符串
p|输出指针地址
lu|32 位无符号整数
llu|64 位无符号整数

flags|说明
-|-|
-|在给定的字段宽度内左对齐，默认是右对齐
+|强制在结果之前显示加号或减号
#|与 `o`、`x` 或 `X` 一起使用时，非零值前面会分别显示 `0`、`0x` 或 `0X`
0|在指定填充 padding 的数字左边放置零 `0`，而不是空格
空格|如果没有写入任何符号，则在该值前面插入一个空格

## fprintf

```cpp
int fprintf(FILE *stream, const char *format, ...);
```

发送格式化输出到流 `stream` 中

## sprintf

```cpp
int sprintf ( char * str, const char * format, ... );
```

发送格式化输出到 `str` 所指向的字符串

## snprintf

```cpp
int snprintf (char * s, size_t n, const char * format, ... );
```

## vprintf

```cpp
int vprintf ( const char * format, va_list arg );
```

## vfprintf

```cpp
int vfprintf(FILE *stream, const char *format, va_list arg)
```

## vsprintf

```cpp
int vsprintf( char *buffer, const char *format, va_list vlist );
```

## vsnprintf

```cpp
int vsnprintf (char * s, size_t n, const char * format, va_list arg );
```
