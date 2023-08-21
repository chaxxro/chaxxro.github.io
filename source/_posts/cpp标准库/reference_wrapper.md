---
toc:
  enable: true
  number: false
  max_depth: 3
title: reference_wrapper
date: 2023-05-29 21:21:27
tags: cpp
categories: cpp
---

`std::ref` 用于创建 `std::reference_wrapper` 类型的对象，该类型会保存对象的引用

```cpp
int value = 0;
std::reference_wrapper<int> valueRef = std::ref(value);

value = 100;
std::cout << valueRef.get() << std::endl;  // 输出100
```

- 无法使用 `&` 的场合

```cpp
int value = 0;
std::vector<std::reference_wrapper<int>> valueRefs{};  // 无法使用std::vector<int&>

valueRefs.push_back(std::ref(value));

value = 100;
std::cout << valueRefs[0] << std::endl;  // 输出100
```

- 在进行类型推断时，`&` 会被丢弃的情况

```cpp
int value = 0;
int& valueRef = value;
auto myTuple = std::make_tuple(valueRef);  // myTuple的类型为std::tuple<int>，&被丢弃
auto myTupleRef = std::make_tuple(std::ref(value));
value = 99;
std::cout << std::get<0>(myTuple) << std::endl;  // 输出0
std::cout << std::get<0>(myTupleRef) << std::endl;  // 输出99
```

- 函数式编程，如 `std::bind`，在绑定参数时，使用的是拷贝，而不是引用

```cpp
void MyFunc(int& value0, int& value1) {
    ++value0;
    ++value1;
}

int value0 = 0, value1 = 0;
auto func = std::bind(MyFunc, value0, std::ref(value1));
func();
std::cout << value0 << std::endl;  // 输出0
std::cout << value1 << std::endl;  // 输出1
```
