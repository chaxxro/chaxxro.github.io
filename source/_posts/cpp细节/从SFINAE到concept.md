---
toc:
  enable: true
  number: false
  max_depth: 3
title: 从 SFINAE 到 concept
date: 2024-01-25 16:47:25
tags: cpp
categories: cpp
---

## SFINAE

SFINAE 是 Substitution Failure Is Not An Error 的缩写，是一种 C++ 中的编译期技术，用于在模板实例化过程中，当尝试进行模板参数的替换时，如果出现了替换失败（通常是由于找不到相应的成员函数、操作符等），不会导致编译错误，而是会选择其他可行的模板特化

std::enable_if 就是利用了 SFNIAE，通过在模板参数替换失败时移除特化，实现了在编译期间的条件选择

```cpp
template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };
```

```cpp
template <typename T, typename Enable = void>
struct is_string : std::false_type {};

template <typename T>
struct is_string<T, std::enable_if_t<std::is_same_v<T, std::string> ||
                                      std::is_same_v<T, const char*> ||
                                      std::is_same_v<T, char[]>>> : std::true_type {};

template <typename T, typename = std::enable_if_t<is_string<T>::value, T>>
void fun(T t) {
  std::string v = t;
}


template <typename T, std::enable_if_t<!is_string<T>::value, bool> = true>
void fun(T t) {
  std::cout << "foo fallback\n";
}

int main() {
  fun(1);
  fun("abc");
  fun(1.2);
  return 0;
}
```

## constexpr

`if constexpr` 用于在编译时进行条件判断，从而实现更灵活的模板元编程

`if constexpr` 中的条件表达式在编译时求值，只有符合条件的分支才会被保留，而不符合条件的分支在生成的代码中会被舍弃

```cpp
template <typename T, typename Enable = void>
struct is_string : std::false_type {};

template <typename T>
struct is_string<T, std::enable_if_t<std::is_same_v<T, std::string> ||
                                      std::is_same_v<T, const char*> ||
                                      std::is_same_v<T, char[]>>> : std::true_type {};

template <typename T>
void fun(T t) {
  if constexpr(is_string<T>::value) {
    std::string v = t;
  } else {
   // others
  }
}

int main() {
  fun(1);
  fun("abc");
  fun(1.22);
  return 0;
}
```

## concept

C++20 引入了 `concept`，它提供了一种更加清晰和简洁的方法，用于规定模板类型参数必须满足的条件，以替代传统的通过模板特化和 SFINAE 

```cpp
template<typename T>
concept xxx = bool expression;
```

`concept` 与 `if constexpr` 结合使用

```cpp
template <typename T>
concept is_string = std::is_same_v<T, std::string> ||
                    std::is_same_v<T, const char*> ||
                    std::is_same_v<T, char[]>;

template <typename T>
void fun(T t) {
  if constexpr (is_string<T>) {
    std::string v = t;
    std::cout << "String: " << v << std::endl;
  } else {
    std::cout << "Other type" << std::endl;
  }
}

int main() {
  fun(1); 
  fun("abc"); 
  fun(1.22);
  return 0;
}
```

`concept` 与 `requires` 配合

```cpp
requires { requirement-seq }

requires ( parameter-list (optional) ) { requirement-seq }
```

```cpp
// 使用 requires { requirement-seq } 形式
template <typename T>
concept is_string = std::is_same_v<T, std::string> ||
                    std::is_same_v<T, const char*> ||
                    std::is_same_v<T, char[]>;

// requires 可以在函数名前
template <typename T>
requires StringType<T>
void fun(T t) {
    
}

// requires 可以在函数名后
template <typename T>
void fun(T t) requires StringType<T> {
    
}

// 直接将 concept 放入模板列表
template <StringType T>
void fun(T t) {
    
}

int main() {
    //fun(1); 
    fun("abc");
    //fun(1.22); 
    return 0;
}
```

```cpp
// 使用 requires ( parameter-list (optional) ) { requirement-seq }
template <typename T>
concept StringType = requires (T t){
    requires std::is_same_v<T, std::string> ||
    std::is_same_v<T, const char*> ||
    std::is_same_v<T, char[]>;
};

template <typename T>
concept StringType = requires (T t){
    { t } ->std::convertible_to<std::string>;
};

template <StringType T>
void fun(T t) {
    
}
```

```cpp
// 1. 判断一个对象是否存在某个成员变量
template <typename T>
concept has_x = requires (T v) {
    v.x;
};
template <typename T>
concept has_x_y = requires (T v) {
    v.x;
    v.y;
};

void fun(has_x auto x) {}
void fun(has_x_y auto x) {}

template <typename T>
concept has_x = requires (T v) {
    v.x;
};
template <typename T>
concept has_x_y = has_x<T> && requires (T v) {
    v.y;
};

// 2. 判断某个类是否存在某个成员函数
template <typename T>
concept FuncCall =
requires(T t){
  t.Func();
};

struct C {
  void Func() {}
};

template<typename T>
requires FuncCall<T>
void Func(T t) {
    t.Func();
}

// 3. 判断成员函数返回类型
template <typename T>
concept FuncCall =
requires(T t){
  {t.Func() } -> std::convertible_to<void>;
};

struct C {
  void Func() {}
};

template<typename T>
requires FuncCall<T>
void Func(T t) {
    t.Func();
}
```