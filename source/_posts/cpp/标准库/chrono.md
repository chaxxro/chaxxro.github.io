---
toc:
  enable: true
  number: false
  max_depth: 3
title: chrono
date: 2023-05-29 21:18:45
tags: cpp
categories: cpp
---

## clock

```cpp
std::chrono::system_clock // 系统时钟
// 有静态函数 `now()`、`to_time_t()`、`from_time_t()`

std::chrono::steady_clock // 稳定时钟，完全根据物理是时间向前移动
// 有静态函数 `now()`

std::chrono::high_resolution_clock // 高精度时钟 
// 有静态函数 `now()`
```

## time_point

表示具体的时间点

```cpp
template<class Clock, class Duration = typename Clock::duration>
class time_point;
```

`time_since_epoch()` 用来获得 1970-01-01 00:00:00 到 `time_point` 时间经过的 `duration`

## duration

表示一段时间

```cpp
template <class Rep, class Period = ratio<1>>
class duration;
// Rep 数值类型

template <intmax_t N, intmax_t D = 1>
class ratio;
// ratio 表示用秒表示的时间单位
std::chrono::duration::hours
std::chrono::duration::minutes
std::chrono::duration::seconds
std::chrono::duration::millseconds
std::chrono::duration::microseconds
std::chrono::duration::nanoseconds

// 各个 duration 之间的类型转换
template <class ToDuration, class Rep, class Period>
ToDuration duration_cast(const duration<Rep, Period>);
```

成员函数 `count()` 用来获得一个 `duration` 对象中包含多少个 `ratio` 对象