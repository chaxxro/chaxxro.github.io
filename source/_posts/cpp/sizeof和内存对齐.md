---
toc:
  enable: true
  number: false
  max_depth: 3
title: sizeof 和内存对齐
date: 2023-06-02 20:42:46
tags: cpp
categories: cpp
---

`sizeof` 是一个操作符，返回一个对象或类型所占的内存字节数

## 结构体的内存对齐

结构体在内存组织上是按顺序排列的

结构体的 `sizeof` 涉及到字节对齐问题，字节对齐有利于加快计算机的取值速度

字节对齐：

- 结构体变量的首地址能够被其最宽基本类型成员的大小所整除

- 结构体的每个成员相对于结构体首地址的偏移量（offset）都是成员大小的整数倍，如有需要，编译器会在成员之间加上填充字节

- 结构体的总大小为结构体最宽基本类型成员大小的整数倍，如有需要，编译器会在最末一个成员后加上填充字节

- 类中有虚函数，则添加虚指针，排在类的内存布局的最开始

- 继承时，基类的成员排在基类内存布局的最开始

- 空结构体（不含数据成员）的 `sizeof` 值为 1

```cpp
struct S1
{
    char a;
    int b;
};
// 8
 
struct S2
{
    int b;
    char a;
};
// 8
 
struct S3
{
    int b;
    char a;
    char c;
};
// 8

struct S4
{
};
// 1
```

### 结构体中位域对齐

1. 如果相邻位域字段的类型相同，且其位宽之和小于类型的 `sizeof` 大小，则后面的字段将紧邻前一个字段存储，直到不能容纳为止

2. 如果相邻位域字段的类型相同，但其位宽之和大于类型的 `sizeof` 大小，则后面的字段将从新的存储单元开始，其偏移量为其类型大小的整数倍

3. 当相邻成员的类型不同时，不同的编译器有不同的实现方案，gcc 会压缩存储

4. 如果成员之间穿插着非位域成员，那么不会进行压缩

## 联合体的内存对齐

联合体在内存组织上是重叠式，各成员共享一段内存，整个联合体的 `sizeof` 也就是每个成员 `sizeof` 的最大值

```cpp
union u
{
    int a;
    float b;
    double c;
    char d;
};
// 值为8
```

## 数组

数组的 `sizeof` 值等于数组所占用的内存字节数

- 当字符数组表示字符串时，其 `sizeof` 值将 `/0` 计算进去

- 当数组为形参时，其 `sizeof` 值相当于指针的 `sizeof` 值

```cpp
char a[10];  // 10
char n[] = "abc";  // 4

void funcN(char b[]) {
    int cN = sizeof(b); // 8
}
```

## 普通指针

指针的内存大小当然就等于计算机内部地址总线的宽度

```cpp
char *b = "helloworld";
char *c[10];
double *d;
int **e;
void (*pf)();  

// sizeof(b) 8
// sizeof(*b) 为1
// sizeof(d) 8
// sizeof(*d) 8
// sizeof(e) 8
// sizeof(c) 80
// sizeof(pf) 8
```

## 类的指针和引用

指针的解应用和引用都是数据类型大小，而不是指向所以大小

```cpp
class A {
public:
	virtual void h() {}
};  // 8

class  B: public A
{
public:
	int i;
	virtual void h() {}
};  // 16

B b;
A& a = b;
B& bb = b;
A* ap = &b;
B* bp = &b;
sizeof(a);   // 8
sizeof(bb);  // 16
sizeof(*ap); // 8
sizeof(*bp); // 16
```

## 函数

`sizeof` 也可对一个函数调用求值，其结果是函数返回值类型的大小，需要传入实参但函数并不会被调用，但不可以对返回值类型为空的函数求值

## 类

- 空类的大小为 1 字节

```cpp
class A{};
// 1
```

- 一个类中，虚函数本身、成员函数（静态和非静态）和静态数据都不占用类对象的存储空间

```cpp
class A
{
public:
    char b;
    virtual void fun() {};
    static int c;
    static int d;
    static int f;
};
// 8 + 8 = 16
```

- 对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针

- 普通继承，派生类继承了所有基类的函数与成员，要按照字节对齐来计算大小

```cpp
class A
{
public:
    char a;  // 1
    int b;   // 4
};
// 4 + 4 = 8

class B : A
{
public:
    short a;  // 2
    long b;   // 8
};
// A(4 + 4) + 8 + 8 = 24

class C {
    A a;
    char c;
}
// A(4 + 4) + 4 = 12
```

- 虚函数继承，不管是单继承还是多继承，都是继承了基类的 vptr

```cpp
class A1
{
    virtual void fun(){}
};
// 8

class A2
{
    char a;
    virtual void fun(){}
};
// 16

class D:public A1
{
};
// 8

class E:public A1
{
    char c;
};
// 16

class F:public A2
{
    char c;
};
// 16
```

- 虚继承，继承基类的 vbptr，并添加一个指向基类的虚基类指针 vfptr

```cpp
/*
vptr    虚函数指针
vtptr   虚基类指针
*/

class A
{
	virtual void fun() {}
};
// 8

class B
{
	virtual void fun2() {}
};
// 8

class C : virtual public A, virtual public B
{
public:
	virtual void fun3() {}
};
// 16

class C1 : public A, public B
{
public:
	virtual void fun3() {}
};
// 16

class D : virtual public A {
	virtual void fun() {}
};
// 8

class D1 : A {
	virtual void fun() {}
};
// 8

class E : virtual public A {
	virtual void fun() {}
};
// 8 

class F : public D, public E {
	virtual void fun() {}
};
// 8

class SuperBase {
public:
	int m_nValue;
	void Fun() { cout << "SuperBase1" << endl; }
	virtual ~SuperBase() {}
};
// 16

class Base1 : virtual public SuperBase {
public:
	virtual ~Base1() {}
};
// 24

class Base2 : virtual public SuperBase
{
public:
	virtual ~Base2() {}
};
// 24

class Der :public Base1, public Base2 {
public:
	virtual ~Der() {}
};
// 32
```