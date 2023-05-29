---
toc:
  enable: true
  number: false
  max_depth: 3
title: typeinfo 用法
date: 2023-05-26 19:45:09
tags: cpp
categories: cpp
---

引入头文件 `#include <typeinfo>`

主要包括三个类 `std::type_info`、`std::bad_typeid`、`std::bad_cast`

## std::type_info

`std::type_info` 类保存了类型中编译器特定实现的信息，包括类型的名称以及比较两个类型是否相等或排序顺序的方法

获取 `std::type_info` 对象需要通过 `typeid` 操作符

`std::type_info` 是禁止拷贝构造和拷贝赋值的

```cpp
typeid ( type )
typeid ( expression )
// 顶层的 cv 限制符是会被忽略的 typeid(const T) == typeid(T)
// 当作用于非多态类型时，计算结果发生在编译时
// 当作用于多态类型时，计算结果发生在运行时
```

`std::type_info` 提供成员函数 `std::size_t hash_code()`、`const char* name()`、`bool before(const type_info& rhs)`、`operator==`

```cpp
struct Base { virtual ~Base() = default; };
struct Derived : Base {};

void func(const Base* pb) {
  const auto type = typeid(*pb);
	std::cout << "name: " << type.name() << '\n';  // 4Base
	std::cout << "hash_code: " << type.hash_code() << '\n';  // 4Base
};
 
int main() {
	Base b1;
	Derived d1;
	const Base *pb = &b1;
  // name: 4Base
  // hash_code: 1646098473708828226
  func(pb);
	pb = &d1;
  // name: 7Derived
  // hash_code: 6509159466577508456
  func(pb);
  return 0;
}
```

```cpp
struct A {
    virtual ~A() {}
};
 
struct B : A {};
struct C : A {};
 
using TypeInfoRef = std::reference_wrapper<const std::type_info>;
 
struct Hasher {
  std::size_t operator()(TypeInfoRef code) const {
    return code.get().hash_code();
  }
};
 
struct EqualTo {
  bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const {
    return lhs.get() == rhs.get();
  }
};
 
int main() {
  std::unordered_map<TypeInfoRef, std::string, Hasher, EqualTo> type_names;

  type_names[typeid(int)] = "int";
  type_names[typeid(double)] = "double";
  type_names[typeid(A)] = "A";
  type_names[typeid(B)] = "B";
  type_names[typeid(C)] = "C";

  int i;
  double d;
  A a;

  std::unique_ptr<A> b(new B);
  std::unique_ptr<A> c(new C);
  std::cout << "i is " << type_names[typeid(i)] << '\n';
  std::cout << "d is " << type_names[typeid(d)] << '\n';
  std::cout << "a is " << type_names[typeid(a)] << '\n';
  std::cout << "b is " << type_names[typeid(*b)] << '\n';
  std::cout << "c is " << type_names[typeid(*c)] << '\n';
  // i is int
  // d is double
  // a is A
  // b is B
  // c is C
  return 0;
}
```

## std::bad_typeid

当 `typeid` 应用于多态类型的解引用空指针值时，将引发此类型的异常

## std::bad_cast

当 `dynamic_cast` 的运行时检查失败会抛出此类型的异常