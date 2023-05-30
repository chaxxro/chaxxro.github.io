---
toc:
  enable: true
  number: false
  max_depth: 3
title: type_trait
date: 2023-05-26 19:46:35
tags: cpp
categories: cpp
---

`type_trait` 头文件定义了一系列基于编译时模板的接口，用于查询或修改类型的属性

## 获取类型属性

模板类中都提供了一个静态成员变量 `bool value` 标识结果

从 cpp17 起直接使用 `std::is_xxx_v<T>` 来获取 `std::is_xxx<T>::value`

```cpp
// 在考虑 cv 的情况下，判断是否是同一类型
template< class T, class U >
struct is_same;

template< class Base, class Derived >
struct is_base_of;
```

## 调整类型属性

模板类中定义了一个类型别名 `type` 表示目标类型

```cpp
template< class T >
struct remove_cv;
template< class T >
struct add_cv;

template< class T >
struct remove_const;
template< class T >
struct add_const;

template< class T >
struct remove_volatile;
template< class T >
struct add_volatile;

template< class T >
struct remove_reference;
template< class T >
struct add_rvalue_reference;
template< class T >
struct add_lavalue_reference;
```