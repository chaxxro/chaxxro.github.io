---
toc:
  enable: true
  number: false
  max_depth: 3
title: call_once
date: 2023-05-29 21:18:32
tags: cpp
categories: cpp
---

保证 `call_once` 调用的函数只被执行一次，需要与 `std::once_flag` 配合使用

`std::once_flag` 被设计为对外封闭的，即外部没有任何渠道可以改变 `once_flag` 的值，仅可以通过`std::call_once` 函数修改

```cpp
#include <iostream>
#include <thread>
#include <mutex>

void initialize() {
    std::cout << __FUNCTION__ << std::endl;
}

std::once_flag of;
void my_thread() {
    std::call_once(of, initialize);
}

int main() {
    std::thread threads[10];
    for (std::thread &thr: threads) {
        thr = std::thread(my_thread);
    }
    for (std::thread &thr: threads) {
        thr.join();
    }
    return 0;
}
// 仅输出一次：initialize
```