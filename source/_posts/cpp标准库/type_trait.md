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

如果 `T` 是函数、引用和 cv 属性是，`std::add_const` 会失效

## 类型转换

- `std::decay` 用于类型退化，将右值转换成左值，数组转换成指针，函数转换成指针

```cpp
template< class T >
struct decay;

template <typename T, typename U>
struct decay_equiv : 
    std::is_same<typename std::decay<T>::type, U>::type 
{};
 
int main()
{
    std::cout << std::boolalpha
              << decay_equiv<int, int>::value << '\n'
              << decay_equiv<int&, int>::value << '\n'
              << decay_equiv<int&&, int>::value << '\n'
              << decay_equiv<const int&, int>::value << '\n'
              << decay_equiv<int[2], int*>::value << '\n'
              << decay_equiv<int(int), int(*)(int)>::value << '\n';
```

- `std::enable_if` 主要用于 SFINAE 场景中，通过对模板函数、模板类中的模板类型进行谓词判断，从而使程序能够选择合适的模板函数重载版本或模板类特化版本

```cpp
/*
接受两个模板参数，第一个参数为布尔条件，第二个参数为类型
当条件为真时，有一个成员 typedef，且是第二个模板参数
当条件为假时，不存在成员 typedef
*/
template< bool B, class T = void >
struct enable_if;
template<typename T>
struct enable_if<true, T> { using type = T; };

struct T {
    enum { int_t, float_t } type;
    template <typename Integer,
              std::enable_if_t<std::is_integral<Integer>::value, bool> = true
    >
    T(Integer) : type(int_t) {}
 
    template <typename Floating,
              std::enable_if_t<std::is_floating_point<Floating>::value, bool> = true
    >
    T(Floating) : type(float_t) {} // OK
};
```

- `std::invoke_result` 和 `std::result_of` 获取可调用对象的返回值类型

```cpp
template< class F, class... ArgTypes >
class result_of<F(ArgTypes...)>;

template< class F, class... ArgTypes>
class invoke_result;

struct S {
    double operator()(char, int&);
    float operator()(int) { return 1.0;}
};
 
template<class T>
typename std::result_of<T(int)>::type f(T& t)
{
    std::cout << "overload of f for callable T\n";
    return t(0);
}
 
template<class T, class U>
int f(U u)
{
    std::cout << "overload of f for non-callable T\n";
    return u;
}
 
int main()
{
    std::result_of<S(char, int&)>::type d = 3.14; // d has type double
    static_assert(std::is_same<decltype(d), double>::value, "");
 
    std::invoke_result<S,char,int&>::type b = 3.14;
    static_assert(std::is_same<decltype(b), double>::value, "");
 
    std::result_of<S(int)>::type x = 3.14; // x has type float
    static_assert(std::is_same<decltype(x), float>::value, "");
 
    struct C { double Func(char, int&); };
    std::result_of<decltype(&C::Func)(C, char, int&)>::type g = 3.14;
    static_assert(std::is_same<decltype(g), double>::value, "");
}
```

- `std::conditional` 编译时进行类型选择

```cpp
template< bool B, class T, class F >
struct conditional;

int main() 
{
    typedef std::conditional<true, int, double>::type Type1;
    typedef std::conditional<false, int, double>::type Type2;
    typedef std::conditional<sizeof(int) >= sizeof(double), int, double>::type Type3;
 
    std::cout << typeid(Type1).name() << '\n';
    std::cout << typeid(Type2).name() << '\n';
    std::cout << typeid(Type3).name() << '\n';
}
```