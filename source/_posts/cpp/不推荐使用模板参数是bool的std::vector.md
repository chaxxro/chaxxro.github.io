---
toc:
  enable: true
  number: false
  max_depth: 3
title: 不推荐使用模板参数是 bool 的 std::vector
date: 2023-05-15 19:24:18
tags: cpp
categories: cpp
---

为了优化空间利用，c++98 显示地定义了 `std::vector<bool>`，其中每个 `bool` 只占用 1 bit 的空间而不是 1 byte

由于空间优化，`std::vector<bool>` 并不具备普通标准容器的所有能力和接口

## 源码分析

```cpp
// stl_bvector.h
typedef unsigned long _Bit_type;

struct _Bit_reference {
  _Bit_type* _M_p;
  _Bit_type  _M_mask;

  operator bool() const {
    return !!(*_M_p & _M_mask);
  }
};

templace<typename _Alloc>
class vector<bool, _Alloc> : protected _Bvector_base<_Alloc> {
public:
  typedef bool              value_type;
  typedef _Bit_reference    reference;
  typedef bool              const_reference;
  typedef _Bit_reference*   pointer;
  typedef const bool*       const_pointer;
  
public:
  reference at(size_t __n);
  const_reference at(size_t __n);

  reference front(size_t __n);
  const_reference front(size_t __n);

  reference back(size_t __n);
  const_reference back(size_t __n);

  reference operator[](size_t __n);
  const_reference operator[](size_t __n);
}
```

`std::vector<bool>` 的 `at`、`front()`、`back()` 和 `[]` 并不像普通的 `std::vector<T>` 一样返回 `T&`，而是返回一个代理对象来表示 `bool`