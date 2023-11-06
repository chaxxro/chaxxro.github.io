---
toc:
  enable: true
  number: false
  max_depth: 3
title: bind
date: 2023-05-29 21:25:53
tags: cpp
categories: cpp
---

`std::bind()` 是一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来适应原对象的参数列表

可以只绑定部分参数，减少可调用对象传入的参数

```cpp

template< class F, class... Args >
/*unspecified*/ bind( F&& f, Args&&... args );
 
template< class R, class F, class... Args >
/*unspecified*/ bind( F&& f, Args&&... args );

// 1. 绑定普通函数
double my_divide (double x, double y) {return x/y;}
auto fn_half = std::bind(my_divide, std::placeholders::_1, 2);  
std::cout << fn_half(10) << '\n';    // 5
// 第一个参数是函数名，普通函数做实参时，会隐式转换成函数指针，等价于 std::bind (&my_divide,_1,2)
// _1表示占位符，位于 <functional> 中，std::placeholders::_1，表示第一个被传入的参数


// 2. 绑定一个成员函数
struct Foo 
{
    void print_sum(int n1, int n2)
    {
        std::cout << n1+n2 << '\n';
    }
    int data = 10;
};
int main() 
{
    Foo foo;
    auto f = std::bind(&Foo::print_sum, &foo, 95, std::placeholders::_1);
    f(5); // 100
}
// 第一个参数表示对象的成员函数的指针，第二个参数表示对象的地址
// 必须显示的指定 &Foo::print_sum，因为编译器不会将对象的成员函数隐式转换成函数指针
// 必须在 Foo::print_sum 前添加&
// 使用对象成员函数的指针时，必须要知道该指针属于哪个对象，因此第二个参数为对象的地址 &foo


// 3. 绑定一个引用参数 
// 不是占位符的参数将拷贝到 std::bind 返回的可调用对象中
// 但可以使用 std::ref 来传递引用
ostream & print(ostream &os, const string& s, char c)
{
    os << s << c;
    return os;
}

int main()
{
    std::vector<string> words{"helo", "world", "this", "is", "C++11"};
    std::ostringstream os;
    char c = ' ';
    std::for_each(words.begin(), words.end(), 
                   [&os, c](const string & s){os << s << c;} );
    std::cout << os.str() << std::endl;

    std::ostringstream os1;
    // std::ostream 不能拷贝，若希望传递给 std::bind 一个对象而不拷贝它，就必须使用标准库提供的 std::ref 函数
    std::for_each(words.begin(), words.end(),
                  std::bind(print, std::ref(os1), _1, c));
    std::cout << os1.str() << std::endl;
}

void f(int& x) {
  std::cout <<"in f " << x << std::endl;
  x += 1;
}

int main() {
  int x = 0;
  auto ff = std::bind(f, x);

  std::cout << "s0 "<< x << std::endl;  // s0 0
  ff();  // in f 0
  std::cout << "s1 "<< x << std::endl;  // s1 0
  ff();  // in f 1
  std::cout << "s2 "<< x << std::endl; // s2 0

  return 0;
}
```
