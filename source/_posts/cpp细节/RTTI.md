---
toc:
  enable: true
  number: false
  max_depth: 3
title: RTTI
date: 2023-08-09 16:30:17
tags: cpp
categories: cpp
---

RTTI（Runtime Type Identification）运行时类型识别，指的是程序在运行的时候才确定需要用到的对象是什么类型的，用于在运行时而不是编译时获取有关对象的信息

RTTI 可以通过特有的方式来告诉调用方其所调用的对象具体信息，一般有 `typeid` 操作符、`type_info` 类和 `dynamic_cast` 操作符

## typeid 和 type_info

`typeid` 操作符的结果是 `type_info` 对象的引用，或者说 `typeid` 表达式的类型是 `const std::type_info&`

`std::type_info` 存储了对象的基本信息。如果对象至少包含一个虚函数，那么 `typeid` 是运行时的事情，否则在编译期就能获取其具体类型

对于存在虚函数的类来说，其对象的 `type_info` 存储在该类的虚函数表中。在运行时刻，根据虚函数指针的实际指向，获取其 `type_info` 信息从而进行相关操作

## dynamic_cast

`dynamic_cast` 是 C++ 中几个常用的类型转换符之一，其通过类型信息 `type_info` 进行相对安全的类型转换

在转换时，会检查转换的 src 对象是否真的可以转换成 dst 类型。对于指针类型转换，如果失败则返回 `nullptr`，而对于引用转换失败就抛出 `bad_cast`

`dynamic_cast` 转换符只能用于含有虚函数的类，因此其常常用于运行期，对于不包括虚函数的类，完全可以使用其它几个转换符在编译期进行转换

`dynamic_cast` 向上转换是静态操作，在编译阶段完成