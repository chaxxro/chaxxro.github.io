---
toc:
  enable: true
  number: false
  max_depth: 3
title: libcurl
date: 2023-11-09 11:59:59
tags: benchmark
categories: 工具自查
---

在基于 libcurl 的程序里，主要采用回调函数的形式完成传输任务，用户在启动传输前设置好各类参数和回调函数，当满足条件时 libcurl 将调用用户的回调函数实现特定功能

## 基本函数

### CURLcode curl_global_init(long flags)

函数只能用一次，但在调用 `curl_global_cleanup` 后仍然可再用

`curl_global_init` 是不保证线程安全的

```cpp
CURL_GLOBAL_ALL         // 初始化所有的可能的调用。
CURL_GLOBAL_SSL         // 初始化支持安全套接字层。
CURL_GLOBAL_WIN32       // 初始化 win32 套接字库。
CURL_GLOBAL_NOTHING     // 没有额外的初始化
```

### void curl_global_cleanup(void)

在结束libcurl使用的时候，用来对curl_global_init做的工作清理


### CURL *curl_easy_init( )

用来初始化一个 `CURL` 指针，相应的在调用结束时要用 `curl_easy_cleanup` 清理

一般 `curl_easy_init` 意味着一个会话的开始. 它会返回一个 `CURL*` 一般都用在 easy 系列的函数中

### void curl_easy_cleanup(CURL *handle)

结束一个会话


### CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter)

告诉 libcurl 程序将有如何的行为

`parameter` 既可以是个函数的指针，也可以是某个对象的指针，也可以是个 `long` 变量，其它取决于 `option`

- `CURLOPT_URL`：访问的 URL

- `CURLOPT_WRITEFUNCTION`：回调函数原型为 `size_t function( void *ptr, size_t size, size_t nmemb, void *stream)`，函数将在接收到数据后被调用。libcurl 提供一个默认的回调函数，它只是简单的将接收到的数据打印到标准输出

- `CURLOPT_WRITEDATA`：用于表明 `CURLOPT_WRITEFUNCTION` 函数中的 `stream` 指针的来源

- `CURLOPT_HEADERFUNCTION`：回调函数原型为 `size_t function( void *ptr, size_t size,size_t nmemb, void *stream)`，一旦接收到 http 头部数据后将调用该函数

- `CURLOPT_HEADERDATA`：用于表明 `CURLOPT_HEADERFUNCTION` 函数中的 `stream` 指针的来源

- `CURLOPT_READFUNCTION`：读取数据传递给远程时的回调函数，函数原型是 `size_t function(void *ptr, size_t size, size_t nmemb,void *stream)`

- `CURLOPT_READDATA`：表明 `CURLOPT_READFUNCTION` 的 `stream` 指针来源

- `CURLOPT_TIMEOUT`：传输时间

- `CURLOPT_CONNECTIONTIMEOUT`：连接等待时间

- `CURLOPT_FOLLOWLOCATION`：重定位URL

- `CURLOPT_RANGE`：指定 `char*` 参数用于指明 http 域的 RANGE 头域

- `CURLOPT_RESUME_FROM`：传递一个 `long` 参数指定希望开始传递的偏移量

### CURLcode curl_easy_perform(CURL *handle)

在 `curl_easy_setopt` 完成后调用，让设置的 `option` 运作起来

- `CURLE_OK` 任务完成

- `CURLE_UNSUPPORTED_PROTOCOL` 不支持的协议

- `CURLE_COULDNT_CONNECT` 不能连接到远程主机或者代理

- `CURLE_REMOTE_ACCESS_DENIED` 访问被拒绝

- `CURLE_HTTP_RETURNED_ERROR` Http 返回错误

- `CURLE_READ_ERROR` 读本地文件错误

可以通过 `const char *curl_easy_strerror(CURLcode errornum)` 获取详细的错误描述字符串