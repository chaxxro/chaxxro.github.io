---
toc:
  enable: true
  number: false
  max_depth: 3
title: new 的各种姿势
date: 2023-06-02 20:37:52
tags: cpp
categories: cpp
---

|分配|释放|类型|能否重载|
|-|-|-|-|
`malloc()`|`free()`|C 函数|不能
`new`|`delete`|C++ 关键字|不能
`operator new()`|`operator delete()`|C++ 函数|能
`std::allocator<T>::allocate()`|`std::allocator<T>::deallocate()`|C++ 标准库|能

## new 和 delete

C++ 则提供了两个关键字 `new` 和 `delete`

使用 `new` 操作符申请内存分配时无须指定内存块的大小，编译器会根据类型信息自行计算

`new` 会调用 `operator new` 分配内存并调用相应的构造函数

`delete` 会调用相应的析构函数并调用 `operaotr delete` 释放内存

`new` 操作符内存分配成功时，返回的是对象类型的指针，类型严格与对象匹配，无须进行类型转换，故 `new` 是符合类型安全性的操作符

```cpp
new ( type ) initializer(optional)
new new-type initializer(optional) // new-type 不能有括号

new int(*[10])();    // error: parsed as (new int) (*[10]) ()
new (int (*[10])()); // okay: allocates an array of 10 pointers to functions

// placement new
new (placement-params) ( type ) initializer(optional)
new (placement-params) new-type initializer(optional)	

// 开辟单地址空间
int *p = new int;  // 开辟大小为 sizeof(int) 空间
int *q = new int(5);  // 开辟大小为 sizeof(int) 的空间，并初始化为 5

// 开辟数组空间
// 一维
int *a = new int[100]{0};  // 开辟大小为 100 的整型数组空间，并初始化为 0
// 二维
int (*a)[6] = new int[5][6];
// 三维
int (*a)[5][6] = new int[3][5][6];
// 四维及以上以此类推
```

## operator new 和 operator delete

`operator new` 和 `operator delete` 是函数，底层是 `malloc()` 和 `free()`

只分配所要求的空间，不调用相关对象的构造函数

当无法满足所要求分配的空间时，如果有 `new_handler` 则调用 `new_handler`，否则如果使用 `nothrow` 没要求不抛出异常，则执行 bad_alloc 异常，否则返回 0

`operator new` 和 `operator delete` 可以被重载：

- 重载时，返回类型必须声明为 `void*`

- 重载时，第一个参数类型必须为表达要求分配空间的大小，类型为 `size_t`

- 重载时，可以带其它参数

使用 `operator new` 分配的空间必须使用 `operator delete` 来释放

```cpp
void* operator new  ( std::size_t count );
void* operator new  ( std::size_t count, void* ptr );
void* T::operator new  ( std::size_t count );
void* T::operator new  ( std::size_t count, user-defined-args... );

void* operator new(std::size_t sz)
{
    std::printf("1) new(size_t), size = %zu\n", sz);
    if (sz == 0)
        ++sz;
 
    if (void *ptr = std::malloc(sz))
        return ptr;
 
    throw std::bad_alloc{};
}
 
void* operator new[](std::size_t sz)
{
    std::printf("2) new[](size_t), size = %zu\n", sz);
    if (sz == 0)
        ++sz;
 
    if (void *ptr = std::malloc(sz))
        return ptr;
 
    throw std::bad_alloc{};
}
 
void operator delete(void* ptr) noexcept
{
    std::puts("3) delete(void*)");
    std::free(ptr);
}
 
void operator delete(void* ptr, std::size_t size) noexcept
{
    std::printf("4) delete(void*, size_t), size = %zu\n", size);
    std::free(ptr);
}
 
void operator delete[](void* ptr) noexcept
{
    std::puts("5) delete[](void* ptr)");
    std::free(ptr);
}
 
void operator delete[](void* ptr, std::size_t size) noexcept
{
    std::printf("6) delete[](void*, size_t), size = %zu\n", size);
    std::free(ptr);
}
 
int main()
{
    int* p1 = new int;
    delete p1;
 
    int* p2 = new int[10];
    delete[] p2;
}


class A {
private:
    int a;

public:
    // 重载 ::operator new
    static void* operator new(size_t size) {

    }
    // 重载 ::operator new[]
    static void* operator new[](size_t size) {

    }

    // 重载 ::operator delete
    static void operator delete(void * pt) {

    }
    // 重载 ::operator delete[]
    static void operator delete[](void * pt) {

    }
}
```

## placement new

placement new 是重载 `operator new` 的一个标准、全局的版本

```cpp
void *operator new( size_t, void * p ) throw() { return p; }
```

允许用户把一个对象放到一个特定的地方，达到调用构造函数的效果

```cpp
class X {
public:
    X() { std::cout << "constructor of X" << std::endl; }
    ~X() { std::cout << "destructor of X" << std::endl;}
    void SetNum(int n) {
        num = n;
    }

    int GetNum() {
        return num;
    }

private:
    int num;
};

int main() {
    char* buf = new char[sizeof(X)];
    X *px = new(buf) X;
    px->SetNum(10);
    std::cout << px->GetNum() << std::endl;
    px->~X();
    delete []buf;
    return 0;
}
```

## malloc 和 free

C 语言提供了 `malloc()` 和 `free()` 两个系统函数，完成对堆内存的申请和释放，`malloc()/free()` 是库函数，需要头文件支持

`malloc()` 需要显式地指出所需内存的尺寸

```cpp
int (*p)[3] = (int(*)[3])malloc(sizeof(int) * 5 * 3);
```

`malloc` 和 `free` 只是分配和释放内存

`malloc` 内存分配成功则是返回 `void*`，需要通过强制类型转换将 `void*` 指针转换成需要的类型