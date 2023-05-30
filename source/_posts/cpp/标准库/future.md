---
toc:
  enable: true
  number: false
  max_depth: 3
title: future
date: 2023-05-29 21:19:53
tags: cpp
categories: cpp
---

使用 `std::future` 的 `get` 方法来获取其它线程的结果

```cpp
enum class future_status
{
    ready,
    timeout,
    deferred
};

template <class R>
class future
{
public:
    // retrieving the value
    R get();
    // functions to check state
    bool valid() const noexcept;

    void wait() const;
    template <class Rep, class Period>
    future_status wait_for(const chrono::duration<Rep, Period>& rel_time) const;
    template <class Clock, class Duration>
    future_status wait_until(const chrono::time_point<Clock, Duration>& abs_time) const;

    shared_future<R> share() noexcept;
};
```

## `get()` 

该函数会一直阻塞，直到获取到结果或异步任务抛出异常

## `share()`

`std::future` 允许 `move`，但是不允许拷贝

`std::shared_future` 允许 `move`，允许拷贝，并且具有和 `std::future` 同样的成员函数

当调用 `share` 后，`std::future` 对象就不再和任何共享状态关联，其 `valid` 函数也会变为 `false`

## `wait()`

等待直到数据就绪。数据就绪时，通过 `get` 函数，无等待即可获得数据

## `wait_for` 和 `wait_until`

`wait_for` 、`wait_until` 主要是用来进行超时等待的

返回值有 3 种状态：

1. `ready` - 数据已就绪，可以通过get获取了

2. `meout` - 超时，数据还未准备好

3. `deferred` - 这个和 `std::async` 相关，表明无需 `wait`，异步函数将在 `get` 时执行

## `valid()`

判断当前 `std::future` 实例是否有效

`std::future` 主要是用来获取异步任务结果的，作为消费方出现，单独构建出来的实例没意义，因此其 `valid` 为 `false`

当与其它生产方(Provider)通过共享状态关联后，`valid` 才会变得有效， `std::future` 才会发挥实际的作用

C++11 中有下面几种 Provider，从这些 Provider 可获得有效的 `std::future` 实例：

1. `std::async`
2. `std::promise::get_future`
3. `std::packaged_task::get_future`