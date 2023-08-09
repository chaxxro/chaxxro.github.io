---
toc:
  enable: true
  number: false
  max_depth: 3
title: pimpl
date: 2023-05-11 21:05:04
tags: cpp
categories: cpp
---

对于 cpp 而言，提供库给第三方使用时，都需要提供 .h 等头文件，但头文件中可能会暴露大量成员变量和私有函数

因此，可以使用 pimpl(Pointer to Implementation) 方法，将内部变量和私有函数隐藏，仅保留对外接口

```cpp
// 前置声明
// 将所有属于 CSocketClient 的成员变量和私有方法转移到 Impl 中
class Impl;

class CScoketClient {
private:
    Impl* m_pImpl;

public:
    .
    .
    .
}

// 由于 Impl 类是辅助类，没必要单独存在
// 所以一般将其定义为内部类，然后在 .cpp 文件中定义 Impl
class CSocketClient {
private:
    class Impl;
    Impl* m_pImpl;

public:
    .
    .
    .
}
```

pimpl 方法优点：

- 核心数据被隐藏，提高安全性

- 降低了编译依赖，提高编译速度

- 接口与实现分离