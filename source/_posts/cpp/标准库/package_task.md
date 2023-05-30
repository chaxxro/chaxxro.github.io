---
toc:
  enable: true
  number: false
  max_depth: 3
title: package_task
date: 2023-05-29 21:21:10
tags: cpp
categories: cpp
---

`std::packaged_task` 允许传入一个函数，并将函数计算的结果传递给 `std::future`，包括函数运行时产生的异常

`std::packaged_task` 支持 `move`，但不支持拷贝

`std::packaged_task` 封装的函数的计算结果会通过与之联系的 `std::future::get` 获取

`std::package_task` 除了可以通过可调用对象构造外，还支持缺省构造(无参构造)

```cpp
template <class R, class... ArgTypes>
class packaged_task<R(ArgTypes...)>
// R 是一个函数或可调用对象
// ArgTypes 是 R 的形参

#include <thread> 
#include <future>   // std::packaged_task, std::future
#include <iostream>

int sum(int a, int b) 
{
    return a + b;
}

int main() 
{
    std::packaged_task<int(int,int)> task(sum);
    std::future<int> future = task.get_future();

    // std::promise一样，std::packaged_task支持move，但不支持拷贝
    // std::thread的第一个参数不止是函数，还可以是一个可调用对象，即支持operator()(Args...)操作
    std::thread t(std::move(task), 1, 2);
    // 等待异步计算结果
    std::cout << "1 + 2 => " << future.get() << std::endl;

    t.join();
    return 0;
}
/// 输出: 1 + 2 => 3
```

## 有效状态

判断一个 `std::packaged_task` 是否可使用，可通过其成员函数 `valid` 来判断

当通过缺省构造初始化时，由于其未设置任何可调用对象或函数，`valid` 会返回 `false`

只有当 `std::packaged_task` 设置了有效的函数或可调用对象，`valid` 才返回 `true`

```cpp
int main() 
{
    std::packaged_task<void()> task; // 缺省构造、默认构造
    std::cout << std::boolalpha << task.valid() << std::endl; // false

    std::packaged_task<void()> task2(std::move(task)); // 右值构造
    std::cout << std::boolalpha << task.valid() << std::endl; // false

    task = std::packaged_task<void()>([](){});  // 右值赋值, 可调用对象
    std::cout << std::boolalpha << task.valid() << std::endl; // true

    return 0;
}
```

## `std::packaged_task::operator()(ArgTypes...)`

该函数会调用 `std::packaged_task` 对象所封装可调用对象 R，但其函数原型与 R 稍有不同

```cpp
void operator()(ArgTypes... )
```

`operator()` 的返回值是 `void`，即无返回值，因为 `std::packaged_task` 的设计主要是用来进行异步调用，因此 `R(ArgTypes...)` 的计算结果是通过 `std::future::get` 来获取的

```cpp
int main() 
{
    std::packaged_task<void()> convert([](){
        throw std::logic_error("will catch in future");
    });
    std::future<void> future = convert.get_future();

    convert(); // 异常不会在此处抛出

    try 
    {
        future.get();
    } catch(std::logic_error &e) 
    {
        std::cerr << typeid(e).name() << ": " << e.what() << std::endl;
    }

    return 0;
}
/// Clang下输出: St11logic_error: will catch in future
```

## 线程退出

`std::packaged_task::make_ready_at_thread_exit` 函数接收的参数与 `operator()(_ArgTypes...)` 一样，行为也一样，但不会将计算结果立刻反馈给 `std::future`，而是在其执行时所在的线程结束后，`std::future::get` 才会取得结果

## `std::packaged_task::reset`

`std::promise` 仅可以执行一次 `set_value` 或 `set_exception` 函数，但 `std::packagged_task` 可以执行多次，其奥秘就是 `reset` 函数

调用 `reset` 后，需要重新 `get_future` ，以便获取下次 `operator()` 执行的结果

由于是重新构造了 `promise` ，因此 `reset` 操作并不会影响之前调用的 `make_ready_at_thread_exit` 结果，也即之前的定制的行为在线程退出时仍会发生