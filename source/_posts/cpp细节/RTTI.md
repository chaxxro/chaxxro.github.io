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

## 虚函数表

每个存在虚函数的类都存在一个虚函数表 vtable，表的内容不仅只有包含虚函数

在创建类对象时候，对象最前面会有一个指针 vptr，指向类虚函数表的对应位置，需要注意的是并不是指向 vtable 的头

虚函数在 vtable 中的索引是根据函数的声明顺序而来

```cpp
class Base1 {
public:
  void f0() {}
  virtual void f1() {}
  int a;
};

class Base2 {
public:
  virtual void f2() {}
  int b;
};

class Derived1 : public Base1, public Base2 {
public:
  void d() {}
  void f2() {} // override Base2::f2()
  int c;
};

class Derived2 : public Base1, public Base2 {
public:
  void d() {}
  void f1() {} // override Base1::f1()
  int c;
};

int main() {
  Derived1 *d = new Derived1;
  Base1 *b1 = (Base1 *)d;
  Base2 *b2 = (Base2 *)d;

  std::cout << d << " " << b1 << " " << b2 << std::endl;
  return 0;
}
// 转换指针时发生地址变化
// 0x23baeb0 0x23baeb0 0x23baec0

// g++ main.cc -fdump-lang-class
/*
Vtable for Base1
Base1::_ZTV5Base1: 3 entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI5Base1)
16    (int (*)(...))Base1::f1

Class Base1
   size=16 align=8
   base size=12 base align=8
Base1 (0x0x7fb096037960) 0
    vptr=((& Base1::_ZTV5Base1) + 16)

Vtable for Base2
Base2::_ZTV5Base2: 3 entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI5Base2)
16    (int (*)(...))Base2::f2

Class Base2
   size=16 align=8
   base size=12 base align=8
Base2 (0x0x7fb096037a80) 0
    vptr=((& Base2::_ZTV5Base2) + 16)

Vtable for Derived1
Derived1::_ZTV8Derived1: 7 entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI8Derived1)
16    (int (*)(...))Base1::f1
24    (int (*)(...))Derived1::f2
32    (int (*)(...))-16
40    (int (*)(...))(& _ZTI8Derived1)
48    (int (*)(...))Derived1::_ZThn16_N8Derived12f2Ev

Class Derived1
   size=32 align=8
   base size=32 base align=8
Derived1 (0x0x7fb09604d000) 0
    vptr=((& Derived1::_ZTV8Derived1) + 16)
  Base1 (0x0x7fb096037b40) 0
      primary-for Derived1 (0x0x7fb09604d000)
  Base2 (0x0x7fb096037ba0) 16
      vptr=((& Derived1::_ZTV8Derived1) + 48)

Vtable for Derived2
Derived2::_ZTV8Derived2: 6 entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI8Derived2)
16    (int (*)(...))Derived2::f1
24    (int (*)(...))-16
32    (int (*)(...))(& _ZTI8Derived2)
40    (int (*)(...))Base2::f2

Class Derived2
   size=32 align=8
   base size=32 base align=8
Derived2 (0x0x7fb09604d070) 0
    vptr=((& Derived2::_ZTV8Derived2) + 16)
  Base1 (0x0x7fb096037cc0) 0
      primary-for Derived2 (0x0x7fb09604d070)
  Base2 (0x0x7fb096037d20) 16
      vptr=((& Derived2::_ZTV8Derived2) + 40)

*/
```

从 `Base1` 和 `Base2` 的 vtable 可以看出，表中第一行是 offset 且为 0，第二行是一个结构体指针，指向 RTTI 信息，后面才是虚函数的函数指针

从 `Base1` 和 `Base2` 的内存布局可以看出，vptr 位于内存布局开始处，且 vptr 并不指向 vtable，而是第一个虚函数的函数指针

从 `Derived` 的 vtable 可以看