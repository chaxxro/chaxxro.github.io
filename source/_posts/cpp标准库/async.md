---
toc:
  enable: true
  number: false
  max_depth: 3
title: async
date: 2023-05-29 21:12:12
tags: cpp
categories: cpp
---

`std::async` 用于直接创建异步任务，实际上就是创建一个线程执行相应任务，基本上可以代替 `std::thread` 的所有事情，异步任务返回的结果保存在 `std::future` 中

`std::async` 有两种重载形式

```cpp
// 用来推断函数 F 的返回值类型
#define FR typename result_of<typename decay<F>::type(typename decay<Args>::type...)>::type

// 不含执行策略
template <class F, class... Args>
future<FR> async(F&& f, Args&&... args);
// 含执行策略
template <class F, class... Args>
future<FR> async(launch policy, F&& f, Args&&... args);

// 执行策略定义了 async 执行 F 的方式，是一个枚举值
enum class launch 
{
    // 启动一个新线程执行任务
    async,
    // 延迟执行任务，调用 get 或者 wait 时才会执行，不会创建线程，惰性执行在当前线程
    deferred,
};

// 不含加载策略的版本，使用的是 std::launch::async|std::launch::deferred
// 即可能是 std::lauch::async 也可能是 std::lauch::deferred
```

```cpp
int main() {
  auto print = [](char c) {
    for (int i = 0; i < 10; i++) {
      std::cout << c;
      std::cout.flush();
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  };

  // 不同launch策略的效果
  std::launch policies[] = {std::launch::async, std::launch::deferred};
  const char *names[] = {"async   ", "deferred"};
  for (int i = 0; i < sizeof(policies) / sizeof(policies[0]); i++) {
    std::cout << names[i] << ": ";
    std::cout.flush();
    std::future<void> f1 = std::async(policies[i], print, '+');
    std::future<void> f2 = std::async(policies[i], print, '-');
    f1.get();
    f2.get();
    std::cout << std::endl;
  }
  return 0;
}

// async   : +-+-+-+--+-++-+--+-+
// deferred: ++++++++++----------
```

使用 `std::async` 启动的线程如果抛出了异常，这些异常会被捕获并存储在返回的 `std::future` 对象中，调用 `get` 的时候会重新抛出异常