---
toc:
  enable: true
  number: false
  max_depth: 3
title: file
date: 2023-05-31 21:16:43
tags: LinuxApi
categories: LinuxApi
---

## fopen

使用给定的模式打开文件

```cpp
FILE *fopen(const char *filename, const char *mode);
```

`mode` 有下列几种形态字符串:

- `r` 以只读方式打开文件，该文件必须存在

- `r+` 以可读写方式打开文件，该文件必须存在

- `rw+` 读写打开一个文本文件，允许读和写

- `w` 打开只写文件，若文件存在则文件清空

- `w+` 打开可读写文件，若文件存在则文件清空，

- `a` 以附加的方式打开只写文件；若文件不存在，则会建立该文件；如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留

- `a+` 以附加方式打开可读写的文件；若文件不存在，则会建立该文件；如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留

模式字符串都可以再加一个 `b` 字符，用来告诉函数库以二进制模式打开文件

如果不加 `b`，表示默认加了 `t`，表示以文本模式打开文件

## fread

```cpp
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
```

- `ptr` 指向带有最小尺寸 size*nmemb 字节的内存块的指针

- `size` 读取的每个元素的大小，以字节为单位

- `nmemb` 元素的个数

- `stream` 指定了一个输入流

## fwrite

```cpp
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

- `ptr` 指向带有最小尺寸 size*nmemb 字节的内存块的指针

- `size` 写入的每个元素的大小，以字节为单位

- `nmemb` 元素的个数

- `stream` 指定了一个输出流

## fflush

```cpp
int fflush(FILE *stream);
```

刷新 `stream` 的输出缓冲区

## fclose

```cpp
int fclose(FILE *stream);
```

关闭流并刷新所有的缓冲区