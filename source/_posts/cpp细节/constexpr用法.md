---
toc:
  enable: true
  number: false
  max_depth: 3
title: constexpr
date: 2023-06-02 20:02:52
tags: cpp
categories: cpp
---

`constexpr` 可以用来修饰变量、函数、构造函数

任何元素被 `constexpr` 修饰，那么编译器将之看成编译时就能得出常量值的表达式去优化

- 用于变量定义，变量会隐式包含 `const`

```cpp
constexpr int value = 0;
```

- 用于函数或模板函数

```cpp
constexpr int func() {
    return 0;
}

template<class F, class... Args>
constexpr std::invoke_result_t<F, Args...> invoke(F&& f, Args&&... args) 
    noexcept(std::is_nothrow_invocable_v<F, Args...>)
{
    if constexpr (std::is_member_pointer_v<std::decay_t<F>>)
        return detail::invoke_memptr(f, std::forward<Args>(args)...);
    else
        return std::forward<F>(f)(std::forward<Args>(args)...);
}

// 没有 constexpr 之前需要使用 enable_if
struct T {
  enum { int_t, float_t } type;
  template <typename Integer,
            std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
  T(Integer) : type(int_t) {}

  template <
      typename Floating,
      std::enable_if_t<std::is_floating_point<Floating>::value, bool> = true>
  T(Floating) : type(float_t) {} // OK
};

struct TT {
  enum { int_t, float_t } type;
  template<typename P>
  TT(P p) {
    if constexpr (std::is_integral_v<P>)
      type = int_t;
    else if constexpr (std::is_floating_point_v<P>)
      type = float_t;
  }
};

```

- 用于静态数据

```cpp
static constexpr char name[] = "jj"
```