---
toc:
  enable: true
  number: false
  max_depth: 3
title: 优先使用 std::make_shared 函数创建 std::shared_ptr
date: 2023-02-27 22:25:09
tags: cpp 智能指针
categories: cpp
---

## std::shared_ptr 构造函数

直接构造 `shared_ptr` 需要先 `new` 相应的对象

```cpp
template< class Y > 
explicit shared_ptr( Y* ptr );
template< class Y, class Deleter > 
shared_ptr( Y* ptr, Deleter d );
template< class Y, class Deleter, class Alloc > 
shared_ptr( Y* ptr, Deleter d, Alloc alloc );
```

## std::make_shared 函数模板

```cpp
// since c++11
template< class T, class... Args >
shared_ptr<T> make_shared( Args&&... args );
// since c++20
template< class T >
shared_ptr<T> make_shared( std::size_t N );
template< class T >
shared_ptr<T> make_shared();
template< class T >
shared_ptr<T> make_shared( std::size_t N, const std::remove_extent_t<T>& u );
template< class T >
shared_ptr<T> make_shared( const std::remove_extent_t<T>& u );

auto sp0 = std::make_shared<int[5]>();
auto sp1 = std::make_shared<int[]>(5);
```

## 两中创建 `std::shared_ptr` 方法的优缺点

- 异常安全，发生异常时仍释放资源

- `std::make_shared` 比起直接使用 `new` 效率更高

- 构造函数是保护或私有时，无法使用 `std::make_shared`

- `std::make_shared` 无法指定删除器

## `std::make_shared` 为什么是异常安全的

```cpp
class Foo;
void func(std::shared_ptr<Foo>, int value);

// 假设函数形参 value 是调用另一个函数 get_value 获得的
// 直接构造 std::shared_ptr
func(std::shared_ptr<Foo>(new Foo), get_value())
// 使用 std::make_shared 构造 std::shared_ptr
func(std::make_shared<Foo>(), get_value())
```

当直接构造 `std::shared_ptr` 时，需要完成三个步骤

1. `new Foo`

2. `std::shared_ptr<Foo>()`

3. `get_value()`

但编译器不保证执行这三个步骤的顺序，所以当执行顺序是 1-> 3 -> 2 且 `get_value()` 抛出异常时，第一步已经成功初始化的资源便无法回收导致泄漏

使用 `std::make_shared` 时，需要完成两个步骤

1. `get_value`

2. `std::make_shared<Foo>()`

编译器不保证执行这两个步骤的顺序，所以当 `get_value` 发生异常时不会影响 `std::make_shared`，所以使用 `std::make_shared` 是异常安全的

## `std::make_shared` 为什么更高效

### `std::shared_ptr` 内存布局

```cpp
// shared_ptr.h
template<typename _Tp>
class shared_ptr : public __shared_ptr<_Tp>;

// shared_ptr_base.h
template<typename _Tp, _Lock_policy _Lp>
class __shared_ptr : public __shared_ptr_access<_Tp, _Lp>{
public:
  using element_type = typename remove_extent<_Tp>::type;

private:
  element_type* _M_ptr;
  __shared_cout<_Lp> _M_refcount;
};

// shared_ptr_base.h
template<_Lock_policy _Lp>
class __shared_count {
private:
  _Sp_counted_base<_Lp>* _M_pi;
};

// shared_ptr_base.h
template<_Lock_policy _Lp = __default_lock_policy>
class _Sp_counted_base : public _Mutex_base<_Lp> {
private:
  _Atomic_word _M_use_count;
  _Atomic_word _M_weak_count;
};
```

可以看出，`shared_ptr` 内部有两块资源，分别是原始资源 `element_type* _M_ptr` 和控制块 `_Sp_counted_base _M_pi`

### 直接构造 `std::shared_ptr`

直接调用构造函数时，需要先创建原始资源，再创建控制块，即需要通过两次 `new` 创建资源

### 使用 `std::make_shared`

```cpp
// shared_ptr.h
template<typename _Tp, typename _Alloc, typename... _Args>
inline shared_ptr<_Tp> allocate_shared(const _Alloc& __a,
                                       _Args&&... __args) {
    return shared_ptr<_Tp>(_Sp_alloc_shared_tag<_Alloc>{__a},
                          std::forward<_Args>(__args)...);
};

// shared_ptr.h
template<typename _Tp, typename... _Args>
inline shared_ptr<_Tp> make_shared(_Args... __args) {
    typedef typename std::remove_cv<_Tp>::type _Tp_nc;
    return std::allocate_shared<_Tp>(std::allocator<_Tp_nc>(),
                                     std::forward<_Args>(__args)...);
};
```

从源码中可以看到 `std::make_shared` 调用的是 `std::shared_ptr` 私有构造函数 `shared_ptr(_Sp_alloc_shared_tag<_Alloc> __tag, _Args&&... __args)`，而私有构造函数调用相应 `__shared_ptr` 的保护构造函数

```cpp
// shared_ptr_base.h
template<typename _Alloc, typename... _Args>
__shared_ptr(_Sp_alloc_shared_tag<_Alloc> __tag, _Args&&... __args)
: _M_ptr(), _M_refcount(_M_ptr, __tag, std::forward<_Args>(__args)...) {
    _M_enable_shared_from_this_with(_M_ptr);
}

// shared_ptr_base.h
template<typename _Tp, typename _Alloc, typename... _Args>
__shared_count(_Tp*& __p, _Sp_alloc_shared_tag<_Alloc> __a, _Args&&... __args) {
    typedef _Sp_counted_ptr_inplace<_Tp, _Alloc, _Lp> _Sp_cp_type;
    // __a._M_a 是 std::allocator
    typename _Sp_cp_type::__allocator_type __a2(__a._M_a);
    // 只分配一次空间，返回一个 __allocated_ptr
    auto __guard = std::__allocate_guarded(__a2);
    _Sp_cp_type* __mem = __guard.get();
    // placement new
    auto __pi = ::new (__mem) _Sp_cp_type(__a._M_a, std::forward<_Args>(__args)...);
    __guard = nullptr;
    // _Sp_counted_ptr_inplace 是 _Sp_counted_base 子类
    _M_pi = __pi;
    // 这里 __p 是引用变量，给外面的 _M_ptr 赋值
    __p = __pi->_M_ptr();
}

template<typename _Tp, typename _Alloc, _Lock_policy _Lp>
class _Sp_counted_ptr_inplace final : public _Sp_counted_base<_Lp> {
    class _Impl : _Sp_ebo_helper<0, _Alloc> {
        typedef _Sp_ebo_helper<0, _Alloc>	_A_base;

        __gnu_cxx::__aligned_buffer<_Tp> _M_storage;
    };

    _Impl _M_impl;
};
```

构造 `__shared_count` 时，通过引入 `_Sp_counted_ptr_inplace` 将原始数据和控制块组合在一起，达到一次分配内存同时创建两个资源的效果

由于 `std::make_shared` 仅分配一次资源，从而比直接构造 `shared_ptr` 效率更高