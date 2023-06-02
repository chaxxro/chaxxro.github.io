---
toc:
  enable: true
  number: false
  max_depth: 3
title: std::enable_shared_from_this 的实现细节
date: 2023-05-29 21:19:14
tags: cpp 智能指针
categories: cpp
---

## 将 this 指针暴露的隐患

```cpp
struct SomeData;
void SomeAPI(const std::shared_ptr<SomeData>& d) {}

struct SomeData {
  void NeedCallSomeAPI() {
	SomeAPI(std::shared_ptr(this));
  }
};
```

考虑这么个情况，直接使用 `this` 构建 `std::shared_ptr`，但函数调用结束后 `SomeAPI` 的入参会将 `this` 从而导致程序错误

正确做法是使用 `std::enable_shared_from_this`

```cpp
struct SomeData;
void SomeAPI(const std::shared_ptr<SomeData>& d) {}

struct SomeData : public std::enable_shared_from_this<SomeData> {
  void NeedCallSomeAPI() {
	SomeAPI(shared_from_this());
  }
};
```

## enable_shared_form_this 实现

`enable_shared_from_this` 是一个以其派生类为模板类型实参的基类模板，继承它后可调用 `shared_from_this` 获取 `this` 的 `std::shared_ptr`

`std::enable_shared_from_this` 内部使用 `std::weak_ptr` 来帮助完成指针相关的控制数据同步，因为使用 `std::weak_ptr` 是为了防止资源永远不被释放从而必须内存泄漏

```cpp
template<typename _Tp>
class enable_shared_from_this {
protected:
  // 子类必须使用 public 继承，不然不能调用父类构造函数
  constexpr enable_shared_from_this() noexcept {}

private:
  // 友元类，允许 __shared_ptr 能够修改 _M_weak_this
  frind class __shared_ptr;
  // mutable 允许该变量能够被 const 函数修改
  mutable weak_ptr<_Tp> _M_weak_this;
}
```

可以看出 `std::enable_shared_from_this` 的核心代码还是比较简单的，但真正复杂的在 `__shared_ptr` 的构造函数中

```cpp
template<typename _Tp, __Lock_policy _Lp>
class __shared_ptr : public __shared_ptr_access<_Tp, _Lp> {
private:
  friend class __weak_ptr<_Tp, _Lp>;
}
```

当 `std::shared_ptr` 进行初始化时，如果 `T` 是公有继承 `std::enable_shared_from_this<T>`，则才能在编译时使用 `std::enable_if` 和 `std::is_convertible` 来初始化 `_M_weak_this`

## 注意事项

因为 `_M_weak_this` 的初始化依赖 `std::shared_ptr` 的初始化，因此不能对非 `std::shard_ptr` 的对象调用使用 `shared_from_this()` 的函数，所以 `shared_from_this()` 不能在构造函数中调用

```cpp
int main() {
	B b;
	auto sp = b.GetSelf();  // 奔溃
	return 0;
}
```