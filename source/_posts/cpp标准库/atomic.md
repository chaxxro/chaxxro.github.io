---
toc:
  enable: true
  number: false
  max_depth: 3
title: atomic
date: 2023-05-29 21:17:52
tags: cpp
categories: cpp
---

原子操作是不可打断的最低粒度操作，是线程安全的、更高效的线程同步手段

使用原子变量就不需要使用互斥量来保护数据，用起来更简洁

C++11 中所有的原子类都是不允许拷贝、不允许移动的

## std::atomic<T>

```cpp
template <class T>
struct atomic;
template <class T>
struct atomic<T*>;

template <class T>
struct atomic<std::shared_ptr<U>>;
template <class T>
struct atomic<std::weak_ptr<U>>;
```

多线程下读写原子变量，其行为取决于内存模型

C++11 定义了一些基础类型的原子变量，如 `std::atomic_bool`、`std::atomic_char`、`std::atomic_int`、`std::atomic_uint32_t`、`std::atomic_ptrdiff_t` 等

自定义类型的原子变量，需要自定义类型满足连续内存、可以按位拷贝 `memcpy` 和没有虚函数，也就是以下判断都是 `true`

- `std::is_trivially_copyable<T>::value`

- `std::is_copy_constructible<T>::value`

- `std::is_move_constructible<T>::value`

- `std::is_copy_assignable<T>::value`

- `std::is_move_assignable<T>::value`

### 构造函数

```
// 将原子对象放在未初始化的状态中，后续可用 std::atomic_init 初始化
atomic() noexcept = default;
// 用 desired 初始化对象，初始化不是原子性的
constexpr atomic( T desired ) noexcept;
atomic( const atomic& ) = delete;
```

### operator=

```cpp
T operator=( T desired ) noexcept; 
T operator=( T desired ) volatile noexcept;
atomic& operator=( const atomic& ) = delete;
atomic& operator=( const atomic& ) volatile = delete;
```

与大多数赋值运算符不同，原子类型的赋值运算符不会返回左值引用，而是返回一个副本

### is_lock_free

判断 `atomic<T>` 是否是 lock free，因为对于一些类型底层可能会使用锁保证原子性

```cpp
struct A {
  int a[100];
};
struct B {
  int x, y;
};
int main() {
  std::cout << std::boolalpha << "std::atomic<A> is lock free? "
            << std::atomic<A>{}.is_lock_free() << '\n'
            << "std::atomic<B> is lock free? "
            << std::atomic<B>{}.is_lock_free() << '\n';
}
// std::atomic<A> is lock free? false
// std::atomic<B> is lock free? true
```

C++17提供了编译时判断 `is_always_lock_free()`，之所以会出现无锁不确定的情况主要是因为内存对齐

```cpp
static constexpr bool is_always_lock_free = /*implementation-defined*/;
```

### store

操作是原子的，按照所指定的内存顺序赋值

```cpp
void store(T desr, memory_order m = memory_order_seq_cst) noexcept;
void store(T desr, memory_order m = memory_order_seq_cst) volatile noexcept;
```

### load

操作是原子的，按照所指定的内存顺序加载返回当前值

```cpp
T load(memory_order m = memory_order_seq_cst) const volatile noexcept;
T load(memory_order m = memory_order_seq_cst) const noexcept;
```

### exchange

赋值后返回变量赋值前的值，整个操作是原子性的，一个原子的读-修改-写操作

```cpp
T exchange(T desr, memory_order m = memory_order_seq_cst) volatile noexcept;
T exchange(T desr, memory_order m = memory_order_seq_cst) noexcept;
```

### compare_exchange

```cpp
bool compare_exchange_weak(T& expect, T desr, memory_order s, memory_order f) volatile noexcept;
bool compare_exchange_weak(T& expect, T desr, memory_order s, memory_order f) noexcept;
bool compare_exchange_weak(T& expect, T desr, memory_order m = memory_order_seq_cst) volatile noexcept;
bool compare_exchange_weak(T& expect, T desr, memory_order m = memory_order_seq_cst) noexcept;


bool compare_exchange_strong(T& expect, T desr, memory_order s, memory_order f) volatile noexcept;
bool compare_exchange_strong(T& expect, T desr, memory_order s, memory_order f) noexcept;
bool compare_exchange_strong(T& expect, T desr, memory_order m = memory_order_seq_cst) volatile noexcept;
bool compare_exchange_strong(T& expect, T desr, memory_order m = memory_order_seq_cst) noexcept;
```

`compare_exchange` 就是 CAS，在对数据执行写操作前，先比较下数据是否有变更，没有变更的情况下才去执行写操作，否则返回失败

- `*this == expect`，返回 `true` 且将 `desr` 赋值给 `*this`，整个过程是一个读-修改-写操作，对应 `success` 内存序

- `*this != expect`，返回 `false` 且将 `*this` 赋值给 `expect`，整个过程是一个读操作，对应 `failure` 内存序

比较和赋值操作是按位进行的，类似于 `std::memcmp` 和 `std::memcpy`，而不使用构造函数、赋值运算符或比较运算符

```cpp
int main() {
  std::atomic_int a(10);
  int b = 10;
  int c = 20;
  std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
  a.compare_exchange_weak(b, c);
  std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
  a.compare_exchange_weak(b, c);
  std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
  return 0;
}
// a: 10, b: 10, c: 20
// a: 20, b: 10, c: 20
// a: 20, b: 20, c: 20
```

`compare_exchange_weak` 在某些平台会小概率发生即使 `*this == expect` 也仍然返回 `false`，但 `compare_exchange_weak` 性能更好

```cpp
template <typename T> struct node {
  T data;
  node *next;
  node(const T &data) : data(data), next(nullptr) {}
};

template <typename T> class stack {
  std::atomic<node<T> *> head;

public:
  void push(const T &data) {
    node<T> *new_node = new node<T>(data);

    new_node->next = head.load(std::memory_order_relaxed);

    while (!head.compare_exchange_weak(new_node->next, new_node,
                                       std::memory_order_release,
                                       std::memory_order_relaxed))
      ;
  }
};
int main() {
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
}
```

### fetch

```cpp
T fetch_add(T arg, std::memory_order order = std::memory_order_seq_cst);
T fetch_sub(T arg, std::memory_order order = std::memory_order_seq_cst);
T fetch_and(T arg, std::memory_order order = std::memory_order_seq_cst);
T fetch_or(T arg, std::memory_order order = std::memory_order_seq_cst);
T fetch_xor(T arg, std::memory_order order = std::memory_order_seq_cst);
```

将 arg 加或者减去到包含的值并返回在操作之前的值，整个操作是原子的

## std::atomic_flag

提供了标志的管理，标志有三种状态：clear、set 和未初始化状态

- clear：可以理解成 bool 类型的 false

- set：可理解为 bool 类型的 true

### 构造函数

缺省情况下 `atomic_flag` 处于未初始化状态，除非初始化时使用了 `ATOMIC_FLAG_INIT` 宏，则此时 `atomic_flag` 处于 clear 状态

### clear

把 `atomic_flag` 置为 clear 状态

```cpp
void clear(memory_order m = memory_order_seq_cst) volatile noexcept;
void clear(memory_order m = memory_order_seq_cst) noexcept;
```

### test_and_set

检测 flag 是否处于 `set` 状态。如果不是，则将其设置为 `set` 状态，并返回 false，否则返回 true

保证多线程环境下只被设置一次

```cpp
bool test_and_set(std::memory_order order = std::memory_order_seq_cst) volatile noexcept;
bool test_and_set(std::memory_order order = std::memory_order_seq_cst) noexcept;
```

```cpp
#include <atomic>    // atomic_flag
#include <iostream>  
#include <list>      
#include <thread>    

void race(std::atomic_flag &af, int id, int n) {
  for (int i = 0; i < n; i++) {
  }
  // 第一个完成计数的打印：Win
  if (!af.test_and_set()) {
    printf("%s[%d] win!!!\n", __FUNCTION__, id);
  }
}

int main() {
  std::atomic_flag af = ATOMIC_FLAG_INIT;

  std::list<std::thread> lstThread;
  for (int i = 0; i < 10; i++) {
    lstThread.emplace_back(race, std::ref(af), i + 1, 5000 * 10000);
  }

  for (std::thread &thr : lstThread) {
    thr.join();
  }

  return 0;
}
```