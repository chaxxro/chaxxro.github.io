---
toc:
  enable: true
  number: false
  max_depth: 3
title: CRTP
date: 2023-12-06 20:06:13
tags: cpp
categories: cpp
---

CRTP 是 Curiously Recurring Template Pattern 的缩写，中文译为奇异的递归模板模式

```cpp
template <typename T> class Base {
public:
  void interface() { static_cast<T *>(this)->imp(); };
};

class Derived : public Base<Derived> {
public:
  void imp() {
    // 即使没有声明 virtual 函数也实现了多态的功能
    std::cout << "in Derived::imp" << std::endl;
  }
};

int main() {
  Base<Derived> b;
  d.interface();

  return 0;
}
```

Base 类的 `interface`中使用 `static_cast` 进行类型转换，从而调用派生类的成员函数。如果使用 `dynamic_cast` 则转换会发生在运行时，而模板是在编译器就进行了实例化

CRTP 总结起来，其有以下两个特点：

- 继承自模板类

- 派生类将自身作为参数传给模板类

## 颠倒继承

对于 CRTP，在基类中调用派生类的成员函数，扩展了基类的功能。而对于普通继承，则是派生类中调用基类的成员函数，扩展了派生类的功能

## 使用场景

### 静态多态

```cpp
template <typename T> class Base {
public:
  void interface() { static_cast<T *>(this)->imp(); }
  void imp() { std::cout << "in Base::imp" << std::endl; }
};

class Derived1 : public Base<Derived1> {
public:
  void imp() { std::cout << "in Derived1::imp" << std::endl; }
};

class Derived2 : public Base<Derived2> {
public:
  void imp() { std::cout << "in Derived2::imp" << std::endl; }
};

class Derived3 : public Base<Derived3> {};

template <typename T> void fun(T &base) { base.interface(); }

int main() {
  Derived1 d1;
  Derived2 d2;
  Derived3 d3;

  fun(d1);
  fun(d2);
  fun(d3);

  return 0;
}
/*
in Derived1::imp
in Derived2::imp
in Base::imp
*/
```