---
toc:
  enable: true
  number: false
  max_depth: 3
title: std::shared_ptr 和 std::unique_ptr 在释放资源上的不同
date: 2023-02-27 22:26:34
tags: cpp 智能指针
categories: cpp
---

## 问题描述

先来看个 demo

```cpp
namespace Test {
  class Object {
  public:
    using pointer = std::shared_ptr<Object>;
    virtual ~Object() {
      std::cout << "destruct Object" << std::endl;
    };
    // ~Object() {
    //   std::cout << "destruct Object" << std::endl;
    // };
  };

  class RealObject: public Object {
  public:
    RealObject(const std::string& str) {
	  str_ = str;
      std::cout << "construct " << str_ << std::endl;
    }
    ~RealObject() {
      std::cout << "destruct " << str_ << std::endl;
    }

  private:
    std::string str_;
  };

  void testCase() {
    std::shared_ptr<Object> sObj = std::make_shared<RealObject>("shared_ptr");
    std::unique_ptr<Object> uObj = std::make_unique<RealObject>("unique_ptr");
    Object* rObj = new RealObject("raw_ptr");
    delete rObj;
  }
};

int main(int argc, char** argv) {
  Test::testCase();
  return 0;
}

/*
非虚基类析构函数
construct shared_ptr
construct unique_ptr
construct raw_ptr
destruct Object
destruct Object
destruct shared_ptr
destruct Object
*/

/*
虚析构函数
construct shared_ptr
construct unique_ptr
construct raw_ptr
destruct raw_ptr
destruct Object
destruct unique_ptr
destruct Object
destruct shared_ptr
destruct Object
*/
```

从 demo 的输出结果，可以得到下面结论

1. 当基类析构函数是虚函数时，`std::shared_ptr` 和 `std::unique_ptr` 都能正确释放资源

2. 当基类析构函数不是虚函数时，`std::shared_ptr` 可以正确释放资源，而 `std::unique_ptr` 没能正确释放子类资源

3. `std::shared_ptr` 在两种情况下都能正确释放资源，是因为能够正确调用子类析构函数

4. `std::unique_ptr` 在基类析构函数不是虚函数时，只会调用父类析构函数，这跟原始指针的行为时一致的

## 一探究竟

造成 `std::shared_ptr` 和 `std::unqiue_ptr` 在释放资源上不同的原因在它们的构造函数

先来看 `std::shared_ptr` 的构造函数

{% asset_img 1.jpeg %}

从图中可以看到 `std::shared_ptr` 的构造函数是模板函数，因此内部保存了传入的原始指针类型

再来看 `std::unique_ptr` 的构造函数

{% asset_img 2.png %}

`std::unique_ptr` 先内部定一个了一个 `pointer` 类型，该类型取决于 `_Tp`

{% asset_img 3.png %}

`std::unique_ptr` 的构造函数都只接受 `pointer` 类型，因此内部只保存了模板类参数类型的指针，所以当父类析构函数非虚函数时，只会调用父类的析构函数