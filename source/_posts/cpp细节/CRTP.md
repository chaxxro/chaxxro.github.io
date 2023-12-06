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

`Base` 类的 `interface`中使用 `static_cast` 进行类型转换，从而调用派生类的成员函数。如果使用 `dynamic_cast` 则转换会发生在运行时，而模板是在编译器就进行了实例化

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

### 代码复用

```cpp
class Base {
public:
  virtual void PrintType() const {
    std::cout << typeid(*this).name() << std::endl;
  }
};

class Derived : public Base {
public:
  virtual void PrintType() const {
    std::cout << typeid(*this).name() << std::endl;
  }
};
class Derived1 : public Base {
public:
  virtual void PrintType() const {
    std::cout << typeid(*this).name() << std::endl;
  }
};

void PrintType(const Base &base) { base.PrintType(); }

int main() {
  Derived d;
  Derived1 d1;

  PrintType(d);
  PrintType(d1);

  return 0;
}

// 借助 CRTP
template <typename T> class Base {
public:
  void PrintType() {
    T &t = static_cast<T &>(*this);
    std::cout << typeid(t).name() << std::endl;
  }
};

class Derived : public Base<Derived> {};
class Derived1 : public Base<Derived1> {};

template <typename T> void PrintType(T base) { base.PrintType(); }

int main() {
  Derived d;
  Derived1 d1;

  PrintType(d);
  PrintType(d1);

  return 0;
}
```

## 局限性

### 容器存储

`Base` 类实际上是一个模板类，而不是一个实际的类。因此，如果存在名为 `Derived` 和 `Derived1` 的派生类，则基类模板初始化将具有不同的类型

```cpp
// 两个类型的指针
Base<Derived> *b = new Derived;
Base<Derived> *b1 = new Derived1;
```

因为基于 CRTP 方式的指针具有不同的类型，所以不能将 CRTP 基类指针存储在容器中

### 堆栈溢出

```cpp
template <typename T> class Base {
public:
  void PrintType() {
    T &t = static_cast<T &>(*this);

    t.PrintType();
  }
};

class Derived : public Base<Derived> {
  // 此处没有实现PrintType()函数
};

int main() {
  Derived d;
  d.PrintType();

  return 0;
}
```

如果派生类没有实现某个基类中定义的函数，那么调用的是基类的函数，这样容易导致递归调用引起堆栈溢出

可以在基类中重新定义另外一个函数，这样在调用函数时，如果派生类中没有实现这个函数，则会调用基类的另一个函数，这样就避免了因为递归调用而导致的堆栈溢出问题

```cpp
template <typename T> class Base {
public:
  void PrintType() {
    T &t = static_cast<T &>(*this);

    t.PrintTypeImpl();
  }

  void PrintTypeImpl() {}
};

class Derived : public Base<Derived> {
  // 此处没有实现PrintTypeImpl()函数
};

int main() {
  Derived d;

  d.PrintType();

  return 0;
}
```

