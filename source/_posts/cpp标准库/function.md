---
toc:
  enable: true
  number: false
  max_depth: 3
title: function
date: 2023-05-29 21:19:46
tags: cpp
categories: cpp
---

类模板 `std::function` 是一个通用的多态函数包装器，`std::function` 的实例可以存储、复制和调用任何可调用的目标，包括：lamdba 表达式，bind 表达式或其他函数对象，以及指向成员函数和指定数据成员的指针

`std::function` 可以取代函数指针的作用，因为它可以延迟函数的执行，特别适合作为回调函数使用

```cpp
#include <functional>
template< class R, class... Args >
class function<R(Args...)>;
/*
R: 被调用函数的返回类型
Args…：被调用函数的形参
*/

// 1. 普通函数
#include <iostream>
using namespace std;

int f(int a, int b)
{
    return a + b;
}
int main()
{
    function<int(int, int)>func = f;
    cout<<f(1, 2)<<endl;
    return 0;
}

// 2. 函数对象
struct functor
{
public:
    int operator() (int a, int b)
    {
        return a + b;
    }
};
int main()
{
   functor ft;
   function<int(int,int)> func = ft();
   cout<<func(1,2)<<endl;   
   return 0;
}

// 3. 模板函数对象
template<class T>
struct functor
{
public:
    T operator() (T a, T b)
    {
        return a + b;
    }
};
int main()
{
   functor ft;
   function<int(int,int)> func = ft<int>();
   cout<<func(1,2)<<endl;    
   return 0;
}

// 4. lambda表达式
int main()
{
	auto f = [](const int a, const int b) {return a + b; };
	std::function<int(int, int)>func = f;
	cout << func(1, 2) << endl;   
	return 0;
}

// 5. 类静态成员函数
class Plus
{
public:
    static int plus(int a, int b)
    {
        return a + b;
    }
};
int main()
{
    function<int(int, int)> f = &Plus::plus;
    cout << f(1, 2) << endl;
    return 0;
}

// 6. 类成员函数
class Plus
{
public:
    int plus(int a, int b)
    {
        return a + b;
    }
};
int main()
{
    Plus p;
    function<int(Plus&,int, int)> f = &Plus::plus;
    //function<int(const Plus,int, int)> f = &Plus::plus;
    cout << f(p,1, 2) << endl;
    return 0;
}

// 7. 类共有数据
class Plus
{
    Plus(int num_):num(num_){}
	public:
	    int plus(int a, int b)
	    {
	        return a + b;
	    }
	   int  num;
};
int main()
{
    const Plus p(2);
    function<int(const Plus&)> f = &Plus::num;
    //function<int(const Plus)> f = &Plus::num;
    cout << f(p) << endl;                       
    return 0;
}

// 8. 通过bind函数调用类成员函数
class Plus
{
public:
    int plus(int a, int b)
    {
        return a + b;
    }
};
int main()
{
   Plus p;
   // 指针形式调用成员函数
   function<int(int, int)> f = bind(&Plus::plus, &p, placeholders::_1, placeholders::_2);// placeholders::_1是占位符
   // 对象形式调用成员函数
   function<int(int, int)> f1 = bind(&Plus::plus, p, placeholders::_1, placeholders::_2);// placeholders::_1是占位符
   cout << f(1, 2) << endl;  
   cout << f1(1, 2) << endl;                              
   return 0;
}
```