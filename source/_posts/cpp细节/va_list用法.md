---
toc:
  enable: true
  number: false
  max_depth: 3
title: va_list 用法
date: 2023-06-02 20:56:40
tags: cpp
categories: cpp
---

```cpp
void printf(const char* format, ...);
```

可变参数主要两点

- 参数数量可变

- 参数类型可变

```cpp
#include <stdarg.h>

// 指向可变参数列表
typedef char * va_list 

// 初始化 va_list 变量，使其指向第一个变量
// parm_n 作为标识符命名了函数定义（在...前面那个）中变量参数表中最右边参数
// 函数形参入栈顺序是从右到左，栈顶是第一个参数
// 传入 parm_n 使 ap 指向可变参数的地址
va_start(va_list ap, parm_n)

// 展开可变参数
T va_arg( std::va_list ap, T)

// 清除可变参数
void va_end( std::va_list ap )

double stddev(int count, ...) 
{
    double sum = 0;
    double sum_sq = 0;
    std::va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        double num = va_arg(args, double);
        sum += num;
        sum_sq += num*num;
    }
    va_end(args);
    return std::sqrt(sum_sq/count - (sum/count)*(sum/count));
}
 
int main() 
{
    std::cout << stddev(4, 25.0, 27.3, 26.9, 25.7) << '\n';
}
```