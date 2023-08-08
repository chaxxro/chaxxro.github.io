---
toc:
  enable: true
  number: false
  max_depth: 3
title: future 相关异步操作
date: 2023-05-29 21:19:53
tags: cpp
categories: cpp
---

`std::future` 作为异步结果的传输通道，通过 `get()` 可以很方便的获取线程函数的返回值

`std::promise` 用来包装一个值，将数据和 `std::future` 绑定起来

`std::packaged_task` 则用来包装一个调用对象，将函数和 `std::future` 绑定起来，方便异步调用

## std::future

`std::future` 主要是作为消费方用来获取异步任务的结果

`std::future` 允许移动操作，但是不允许拷贝操作

### get

`get()` 会一直阻塞直到获取到结果或异步任务抛出异常

### valid

`std::future` 表示一个共享状态，可以通过 `valid()` 函数查询其共享状态是否有效

一般来说，只有当 `valid()` 返回 `true` 的时候才调用 `get()` 去获取结果，获取完结果后 `valid()` 将返回 `false`

一个有效的 `std::future` 对象只能通过 `std::async()`, `std::promise::get_future` 或者 `std::packaged_task::get_future` 来初始化，由 `std::future` 默认构造函数创建的 `std::future` 对象是无效的

### share

`get()` 会改变其共享状态，也就是说 `get()` 只能被调用一次，多次调用会触发异常。如果想要在多个线程中多次获取产出值需要使用 `std::shared_future`

`std::share()` 返回 `std::shared_future`,`std::shared_future` 允许 `move`，允许拷贝，并且具有和 `std::future` 同样的成员函数

当调用 `share` 后，`std::future` 对象就不再和共享状态关联，其 `valid` 函数也会变为 `false`

### wait

等待直到数据就绪。数据就绪时，通过 `get` 函数，无等待即可获得数据

`wait_for` 、`wait_until` 主要是用来进行超时等待的，返回值有 3 种状态：

1. `std::future_status::ready` 数据已就绪，可以通过 `get` 获取

2. `std::future_status::timeout` 超时，数据还未准备好

3. `std::future_status::deferred` 和 `std::async` 相关，表明无需 `wait`，异步函数将在 `get` 时执行

## std::promise

`std::promise` 是一个模板类 `template<typename R> class promise`，其泛型参数 R 为 `std::promise` 对象保存的值的类型，R 可以是 `void` 类型

作用是在一个线程 t1 中保存一个类型 `typename R` 的值，可供相绑定的`std::future` 对象在另一线程 t2 中获取

`std::promise` 允许移动，但不允许拷贝

```cpp
void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int> accumulate_promise) {
  int sum = std::accumulate(first, last, 0);
  accumulate_promise.set_value(sum); // Notify future
}

void do_work(std::promise<void> barrier) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  barrier.set_value();
}

int main() {
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
  std::promise<int> accumulate_promise;
  std::future<int> accumulate_future = accumulate_promise.get_future();
  std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
                          std::move(accumulate_promise));

  std::cout << "result=" << accumulate_future.get() << '\n';
  work_thread.join();

  std::promise<void> barrier;
  std::future<void> barrier_future = barrier.get_future();
  std::thread new_work_thread(do_work, std::move(barrier));
  barrier_future.wait();
  new_work_thread.join();
}
```

### get_future

通过 `get_future` 获取与 `std::promise` 关联的 `std::future`

一个 `std::promise` 实例只能与一个 `std::future` 关联共享状态，当在同一个 `std::promise` 上反复调用 `get_future` 会抛出 `future_error` 异常

### set_value

`set_value` 可以设置 `std::promise` 中保存的值，该值通过 `std::future` 读取

`set_value` 只能被调用一次，多次调用会抛出 `std::future_error` 异常

事实上 `std::promise::set_xxx` 函数会改变 `std::promise` 的状态为 ready，再次调用时发现状态已要是 ready 了，则抛出异常

如果 `std::promise` 直到销毁时都未设置过任何值，则 `std::promise` 会在析构时自动设置为 `std::future_error`，这会造成 `std::future.get` 抛出 `std::future_error` 异常

`set_value_at_thread_exit` 会在当前线程销毁时设置 `std::promise` 的值

### set_exception

`std::promise::set_exception` 可以设置自定义异常，该异常最终会被传递到 `std::future`，并在其 `get` 函数中被抛出

```cpp
void catch_error(std::future<void> &future) {
  try {
    future.get();
  } catch (std::logic_error &e) {
    std::cerr << "logic_error: " << e.what() << std::endl;
  }
}

int main() {
  std::promise<void> promise;
  std::future<void> future = promise.get_future();

  std::thread thread(catch_error, std::ref(future));
  // 自定义异常需要使用make_exception_ptr转换一下
  promise.set_exception(std::make_exception_ptr(std::logic_error("caught")));

  thread.join();
  return 0;
}
// 输出：logic_error: caught
```

`std::promise` 虽然支持自定义异常，但它并不直接接受异常对象，自定义异常可以通过 `std::make_exception_ptr` 函数转化为 `std::exception_ptr`

`set_exception_at_thread_exit` 等同于 `set_value_at_thread_exit`

### std::promise<void>

`std::promise<void>` 是合法的，此时 `std::promise.set_value` 不接受任何参数，仅用于通知关联的 `std::future.get()` 解除阻塞

## std::packaged_task

`std::packaged_task` 允许传入一个函数，并将函数计算的结果传递给与之关联的 `std::future`，包括函数运行时产生的异常

`std::packaged_task` 支持移动操作，但不支持拷贝操作

`std::package_task` 除了可以通过可调用对象构造外，还支持缺省构造(无参构造)

```cpp
template <class R, class... ArgTypes>
class packaged_task<R(ArgTypes...)>
// R 是一个函数或可调用对象
// ArgTypes 是 R 的形参

#include <thread> 
#include <future>
#include <iostream>

int sum(int a, int b) { return a + b; }

int main() {
  std::packaged_task<int(int, int)> task(sum);
  std::future<int> future = task.get_future();

  std::thread t(std::move(task), 1, 2);
  // 等待异步计算结果
  std::cout << "1 + 2 => " << future.get() << std::endl;

  t.join();
  return 0;
}
/// 输出: 1 + 2 => 3
```

### get_future

通过 `get_future` 获取与 `std::packaged_task` 关联的 `std::future`

一个 `std::packaged_task` 实例只能与一个 `std::future` 关联共享状态，当在同一个 `std::packaged_task` 上反复调用 `get_future` 会抛出 `future_error` 异常

### valid

通过其成员函数 `valid` 来判断 `std::packaged_task` 是否可用

当通过缺省构造初始化时，由于其未设置任何可调用对象或函数，`valid` 会返回 `false`

只有当 `std::packaged_task` 设置了有效的函数或可调用对象，`valid` 才返回 `true`

```cpp
int main() {
  std::packaged_task<void()> task;
  std::cout << std::boolalpha << task.valid() << std::endl;  // false

  std::packaged_task<void()> task2(std::move(task));
  std::cout << std::boolalpha << task.valid() << std::endl;  // false

  task = std::packaged_task<void()>([]() {});
  std::cout << std::boolalpha << task.valid() << std::endl; // true

  return 0;
}
```

### operator()

调用 `std::packaged_task` 对象所封装可调用对象 R，但其函数原型与 R 稍有不同

```cpp
void operator()(ArgTypes... )
```

`operator()` 的返回值是 `void` 无返回值，因为 `std::packaged_task` 的设计主要是用来进行异步调用，因此 `R(ArgTypes...)` 的计算结果是通过 `std::future::get` 来获取的

```cpp
int main() {
  std::packaged_task<void()> convert(
      []() { throw std::logic_error("will catch in future"); });
  std::future<void> future = convert.get_future();

  convert(); // 异常不会在此处抛出

  try {
    future.get();
  } catch (std::logic_error &e) {
    std::cerr << typeid(e).name() << ": " << e.what() << std::endl;
  }

  return 0;
}
// St11logic_error: will catch in future
```

### make_ready_at_thread_exit

`std::packaged_task::make_ready_at_thread_exit` 和 `operator()` 行为一样，但不会将计算结果立刻反馈给 `std::future`，而是在其执行时所在的线程结束后

### reset

`std::promise` 仅可以执行一次 `set_value` 或 `set_exception` 函数，但 `std::packagged_task` 可以执行多次，其奥秘就是 `reset` 函数

调用 `reset` 后，需要重新 `get_future` ，以便获取下次 `operator()` 执行的结果

由于是重新构造了 `promise` ，因此 `reset` 操作并不会影响之前调用的 `make_ready_at_thread_exit` 结果，也即之前的定制的行为在线程退出时仍会发生
