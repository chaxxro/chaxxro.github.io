---
toc:
  enable: true
  number: false
  max_depth: 3
title: promise
date: 2023-05-29 21:21:21
tags: cpp
categories: cpp
---

`std::promise` 是一个模板类 `template<typename R> class promise`，其泛型参数 R 为 `std::promise` 对象保存的值的类型，R 可以是 `void` 类型

作用是在一个线程 t1 中保存一个类型 `typename R` 的值，可供相绑定的`std::future` 对象在另一线程 t2 中获取

`std::promise` 允许 `move` 语义(右值构造，右值赋值)，但不允许拷贝(拷贝构造、赋值)

## 赋值

通过成员函数 `set_value` 可以设置 `std::promise` 中保存的值，该值最终会被与之关联的 `std::future::get` 读取到

`set_value` 只能被调用一次，多次调用会抛出 `std::future_error` 异常

事实上 `std::promise::set_xxx` 函数会改变 `std::promise` 的状态为 ready，再次调用时发现状态已要是 ready 了，则抛出异常

与 `std::promise` 关联的 `std::future` 是通过 `std::promise::get_future` 获取到的，自己构造出来的无效

一个 `std::promise` 实例只能与一个 `std::future` 关联共享状态，当在同一个 `std::promise` 上反复调用 `get_future` 会抛出 `future_error` 异常

```cpp
#include <iostream> 
#include <thread>   
#include <string>   
#include <future>   // std::promise, std::future
#include <chrono>   
using namespace std::chrono;

void read(std::future<std::string> *future)
{
    // future会一直阻塞，直到有值到来
    std::cout << future->get() << std::endl;
}

int main() 
{
    // promise 相当于生产者
    std::promise<std::string> promise;
    // future 相当于消费者, 右值构造
    std::future<std::string> future = promise.get_future();
    // 另一线程中通过future来读取promise的值
    std::thread thread(read, &future);
    // 让read等一会儿:)
    std::this_thread::sleep_for(seconds(1));
    // 
    promise.set_value("hello future");
    // 等待线程执行完成
    thread.join();

    return 0;
}
// hello future
```

如果 `std::promise` 直到销毁时都未设置过任何值，则 `std::promise` 会在析构时自动设置为 `std::future_error`，这会造成 `std::future.get` 抛出 `std::future_error` 异常

```cpp
void read(std::future<int> future)
{
    try 
    {
        future.get();
    } catch(std::future_error &e)
    {
        std::cerr << e.code() << "\n" << e.what() << std::endl;
    }
}

int main()
{
    std::thread thread;
    {
        // 如果promise不设置任何值
        // 则在promise析构时会自动设置为future_error
        // 这会造成future.get抛出该异常
        std::promise<int> promise;
        thread = std::thread(read, promise.get_future());
    }
    thread.join();

    return 0;
}
```

## 异常设置

通过 `std::promise::set_exception` 函数可以设置自定义异常，该异常最终会被传递到 `std::future`，并在其 `get` 函数中被抛出

```cpp
void catch_error(std::future<void> &future)
{
    try 
    {
        future.get();
    } catch (std::logic_error &e) 
    {
        std::cerr << "logic_error: " << e.what() << std::endl;
    }
}

int main() 
{
    std::promise<void> promise;
    std::future<void> future = promise.get_future();

    std::thread thread(catch_error, std::ref(future));
    // 自定义异常需要使用make_exception_ptr转换一下
    promise.set_exception(
        std::make_exception_ptr(std::logic_error("caught")));
    
    thread.join();
    return 0;
}
// 输出：logic_error: caught
```
`std::promise` 虽然支持自定义异常，但它并不直接接受异常对象，自定义异常可以通过 `std::make_exception_ptr` 函数转化为 `std::exception_ptr`

## `std::promise<void>`

`std::promise<void>` 是合法的。此时 `std::promise.set_value` 不接受任何参数，仅用于通知关联的 `std::future.get()` 解除阻塞

## 线程退出

`std::promise::set_value_at_thread_exit` 线程退出时，`std::future` 收到通过该函数设置的值

`std::promise::set_exception_at_thread_exit` 线程退出时，`std::future` 则抛出该函数指定的异常