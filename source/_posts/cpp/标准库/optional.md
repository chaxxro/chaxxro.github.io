---
toc:
  enable: true
  number: false
  max_depth: 3
title: optional
date: 2023-05-29 21:21:04
tags: cpp
categories: cpp
---

`std::nullopt` 是没有值的 `std::optional` 的表达形式，等同于 `{ }`

```cpp
// 空 optiolal
std::optional<int> oEmpty;
std::optional<float> oFloat = nullopt;

std::optional<int> oInt(10);
std::optional oIntDeduced(10);  // type deduction

// make_optional
auto oDouble = std::make_optional(3.0);
auto oComplex = make_optional<complex<double>>(3.0, 4.0);

// in_place
std::optional<complex<double>> o7{in_place, 3.0, 4.0};

// initializer list
std::optional<vector<int>> oVec(in_place, {1, 2, 3});

// 拷贝赋值
auto oIntCopy = oInt;
```

`has_value()` 和 `operator()` 返回是否有值，`value()` 返回这个值

如果没有值并且还调用 `value()`，会抛出一个类型为 `std::bad_optional_access` 的异常

`value_or` 来设置没有值时的默认返回值