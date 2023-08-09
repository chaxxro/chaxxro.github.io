---
toc:
  enable: true
  number: false
  max_depth: 3
title: variant
date: 2023-05-29 21:22:33
tags: cpp
categories: cpp
---

在 C++17 之前，使用 `union` 来定义一个可以存储不同类型的变量

现在可以通过 `std::variant<T1,T2,...>` 来定义一个可以存储不同类型的新变量

`std::variant` 优势在于存储了变量的类型信息和可以存储复杂对象

- `index()` 返回实际存放数据类型的下标

- `std::get<int>` 根据数据类型下标获取数据，若输入下标与 `index()` 不同则报错

- `std::get<T>` 根据数据类型获取数据，若 `T` 不是实际存放数据类型则报错，`T` 需要是唯一的类型

- `std::get_if<int>`、`std::get_if<T>` 与 `std::get` 类似，这里获取的是指针

- `std::holds_alternative<T>` 检查是否存放了 `T` 类型数据，`T` 需要时唯一的类型

- `std::visit<vis, Variant&&... vars>` 接受一个函数 `vis`，将 `vars` 逐一调用 `vis`

```cpp
std::variant<int, double> var;  // var = 0, 默认构造第一个数据类型
```