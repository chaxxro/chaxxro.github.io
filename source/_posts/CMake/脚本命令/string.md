---
toc:
  enable: true
  number: false
  max_depth: 3
title: string
date: 2023-04-19 14:45:28
tags: cmake
categories: cmake
---

## 查找和替换

```cmake
string(FIND <string> <substring> <output_variable> [REVERSE])
```

查找 string 中的 sbustring，将 substring 的索引存储在 output_variable

未找到 substring 返回 -1

`string(FIND)` 将 string 当作 ASCII 串处理

```cmake
string(REPLACE <match_string>
       <replace_string> <output_variable>
       <input> [<input>...])
```

将 input 中所有 match_string 替换成 replace_string，并将结果存储在 output_variable 中 

```cmake
string(REGEX MATCH <regular_expression>
       <output_variable> <input> [<input>...])
```

使用 regular_expression 匹配一次，在匹配前会将所有 input 连接起来，将结果存储在 output_variable

```cmake
string(REGEX MATCHALL <regular_expression>
       <output_variable> <input> [<input>...])
```

使用 regular_expression 尽可能多的匹配，在匹配前会将所有 input 连接起来，将结果存储在 output_variable

```cmake
string(REGEX REPLACE <regular_expression>
       <replacement_expression> <output_variable>
       <input> [<input>...])```
```

使用 regular_expression 尽可能多的匹配，在匹配前会将所有 input 连接起来，使用 replacement_expression 替换后将结果存储在 output_variable

## 修改

```cmake
string(APPEND <string-var> [<input>...])
string(PREPEND <string-var> [<input>...])
string(CONCAT <out-var> [<input>...])
string(JOIN <glue> <out-var> [<input>...])
string(TOLOWER <string> <out-var>)
string(TOUPPER <string> <out-var>)
string(LENGTH <string> <out-var>)
string(SUBSTRING <string> <begin> <length> <out-var>)
string(STRIP <string> <out-var>)
string(GENEX_STRIP <string> <out-var>)
string(REPEAT <string> <count> <out-var>)
```

## 比较

```cmake
string(COMPARE LESS <string1> <string2> <output_variable>)
string(COMPARE GREATER <string1> <string2> <output_variable>)
string(COMPARE EQUAL <string1> <string2> <output_variable>)
string(COMPARE NOTEQUAL <string1> <string2> <output_variable>)
string(COMPARE LESS_EQUAL <string1> <string2> <output_variable>)
string(COMPARE GREATER_EQUAL <string1> <string2> <output_variable>)
```

## 哈希

```cmake
string(<HASH> <out-var> <input>)
```

支持 MD5、SHA1、SHA224、SHA256、SHA384、SHA512、SHA3_224、SHA3_256、SHA3_384、SHA3_512、

## 生成

```cmake
string(ASCII <number>... <out-var>)
string(HEX <string> <out-var>)
string(CONFIGURE <string> <out-var> [...])
string(MAKE_C_IDENTIFIER <string> <out-var>)
string(RANDOM [<option>...] <out-var>)
string(TIMESTAMP <out-var> [<format string>] [UTC])
string(UUID <out-var> ...)
```

## json

```cmake
string(JSON <out-var> [ERROR_VARIABLE <error-var>]
       {GET | TYPE | LENGTH | REMOVE}
       <json-string> <member|index> [<member|index> ...])
string(JSON <out-var> [ERROR_VARIABLE <error-var>]
       MEMBER <json-string>
       [<member|index> ...] <index>)
string(JSON <out-var> [ERROR_VARIABLE <error-var>]
       SET <json-string>
       <member|index> [<member|index> ...] <value>)
string(JSON <out-var> [ERROR_VARIABLE <error-var>]
       EQUAL <json-string1> <json-string2>)
```