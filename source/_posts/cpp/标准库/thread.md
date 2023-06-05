---
toc:
  enable: true
  number: false
  max_depth: 3
title: thread
date: 2023-05-29 21:22:04
tags: cpp
categories: cpp
---

```cpp
#include <iostream>
#include <thread>

void function_1() {
    std::cout << "I'm function_1()" << std::endl;
}

int main() {
    std::thread t1(function_1);
    // do other things
    t1.join();
    return 0;
}

/*
1. 构建一个 std::thread 对象 t1，构造的时候传递了一个参数，这个参数是一个函数，这个函数就是这个线程的入口函数，函数执行完了，整个线程也就执行完了

2. 线程创建成功后，就会立即启动，并没有一个类似 start() 的函数来显式的启动线程

3. 一旦线程开始运行，就需要在线程对象销毁之前显式的决定是要等待它完成 (join)，或者分离它让它自行运行 (detach)

4. Linux 环境下，pthread 不是 linux 下的默认的库，也就是在链接的时候，无法找到 phread 库中哥函数的入口地址，于是链接会失败，附加要加 -lpthread 参数即可解决
*/

```

线程对象和对象内部管理的线程的生命周期并不一样，如果线程执行的快，可能内部的线程已经结束了，但是线程对象还活着，也有可能线程对象已经被析构了，内部的线程还在运行

线程被分离之后，即使该线程对象被析构了，线程还是能够在后台运行，只是由于对象被析构了，主线程不能够通过对象名与这个线程进行通信

```cpp
void function_1() {
    // 延时 500ms 为了保证 test() 运行结束之后才打印
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    std::cout << "I'm function_1()" << std::endl;
}

void test() {
    std::thread t1(function_1);
    t1.detach();
    // t1.join();
    std::cout << "test() finished" << std::endl;
}

int main() {
    test();
    // 让主线程晚于子线程结束
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // 延时1s
    return 0;
}

// 使用 t1.detach()时
// test() finished
// I'm function_1()

// 使用 t1.join()时
// I'm function_1()
// test() finished

/*
1. 由于线程入口函数内部有个 500ms 的延时，所以在还没有打印的时候，test() 已经执行完成了，t1 已经被析构了，但是它负责的那个线程还是能够运行，这就是 detach() 的作用

2. 如果去掉 main 函数中的 1s 延时，会发现什么都没有打印，因为主线程执行的太快，整个程序已经结束了，那个后台线程被 C++ 运行时库回收了

3. 如果将 t1.detach() 换成 t1.join()，test() 会在 t1 线程执行结束之后，才会执行结束

join()：主线程会一直阻塞着，直到子线程完成，join() 函数的另一个任务是回收该线程中使用的资源

detach()：线程放在后台运行，所有权和控制权被转交给 C++ 运行时库，以确保与线程相关联的资源在线程退出后能被正确的回收；线程被分离之后，即使该线程对象被析构了，线程还是能够在后台运行，只是由于对象被析构了，主线程不能够通过对象名与这个线程进行通信

一旦一个线程被分离了，就不能够再被 join 了；可以使用 joinable() 函数判断一个线程对象能否调用join()
*/
```

## 启动线程

创建一个 `std::thread` 对象，就会启动一个线程，并使用该 `std::thread` 对象来管理该线程，其构造函数需要的是可调用（callable）类型，只要是有函数调用类型的实例都是可以的，可传入类型：函数、 lambda 表达式、重载了 `()` 运算符的类的实例

```cpp
// 1. 传入函数
void do_task();
std::thread(do_task);

// 2. lambda 表达式
for (int i = 0; i < 4; i++)
{
    thread t([i]{
        cout << i << endl;
    });
    t.detach();
}

// 3. 重载了()运算符的类的实例
class Task
{
public:
    void operator()(int i)
    {
        cout << i << endl;
    }
};

int main()
{
    
    for (uint8_t i = 0; i < 4; i++)
    {
        Task task;
        thread t(task, i);
        t.detach(); 
    }
}

// 4. 类中的方法
class Test
{
public:
    void Func(int a)
    {
        a = 1;
    }
}

int main()
{
    Test test;
    std::thread t(&Test::Func, &test, 10);
}

// thread 构造函数无法推导重载函数

/*
当线程启动后，一定要在和线程相关联的 thread 销毁前，确定以何种方式等待线程执行结束

detach 方式，启动的线程自主在后台运行，当前的代码继续往下执行，不等待新线程结束

join 方式，阻塞当前代码，等待启动的线程完成，才会继续往下执行

需要注意：创建新线程的作用域结束后，有可能线程仍然在执行，这时局部变量随着作用域的完成都已销毁，如果线程继续使用局部变量的引用或者指针，会出现意想不到的错误，并且这种错误很难排查
以 detach 的方式执行线程时，要将线程访问的局部数据复制到线程的空间（使用值传递），一定要确保线程没有使用局部变量的引用或者指针，除非你能肯定该线程会在局部作用域结束前执行结束
使用 join 方式的话就不会出现这种问题，它会在作用域结束前完成退出
*/
```

```cpp
/*
当决定以 detach 方式让线程在后台运行时，可以在创建 thread 的实例后立即调用 detach，这样线程就会和 thread 的实例分离，即使出现了异常，thread 的实例被销毁仍然能保证线程在后台运行

线程以 join 方式运行时，需要在主线程的合适位置调用 join 方法，如果调用 join 前出现了异常，thread 被销毁，线程就会被异常所终结

为了避免异常将线程终结，或者由于某些原因，例如线程访问了局部变量，就要保证线程一定要在函数退出前完成，就要保证要在函数退出前调用join
*/

void func() {
    thread t([]{
        cout << "hello C++ 11" << endl;
    });

    try
    {
        do_something_else();
    }
    catch (...)
    {
        t.join();
        throw;
    }
    t.join();
}
// 上面代码能够保证在正常或者异常的情况下，都会调用 join 方法，这样线程一定会在函数 func 退出前完成

// 一种比较好的方法是资源获取即初始化（RAII)，该方法提供一个类，在析构函数中调用 join
class thread_guard
{
    thread &t;
public :
    explicit thread_guard(thread& _t) :
        t(_t){}

    ~thread_guard()
    {
        if (t.joinable())
            t.join();
    }

    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
};

void func(){

    thread t([]{
        cout << "Hello thread" <<endl ;
    });

    thread_guard g(t);
}
```

## 向线程传递参数

当需要向线程传递参数时，可以直接通过 `std::thread` 的构造函数依次传入参数即可

需要注意的是，默认的会将传递的参数以拷贝的方式复制到线程空间，即使参数的类型是引用

```cpp
void func(int a,const string str);
thread t(func,3,string("hello"));

class _tagNode
{
public:
    int a;
    int b;
};

void func(_tagNode &node)
{
    node.a = 10;
    node.b = 20;
}

void f()
{
    _tagNode node;

    thread t(func, std::ref(node));
    t.join();

    cout << node.a << endl ;
    cout << node.b << endl ;
}
// 在线程内，将对象的字段 a 和 b 设置为新的值，但是在线程调用结束后，这两个字段的值并不会改变
// 引用的实际上是局部变量 node 的一个拷贝，而不是 node 本身
// 在将对象传入线程的时候，调用std::ref，将 node 的引用传入线程，而不是一个拷贝 thread t(func,std::ref(node))
```

当需要执行的函数形参是左值引用时，必须使用 `std::ref` 构建一个 `std::reference_wrapper` 进行参数传递，因为 `std::reference_wrapper<T>` 有对 `T&` 的隐式转换

## 线程暂停

`std::thread` 没有直接提供暂停函数从外部让线程暂停，但可以使用 `std::this_thread::sleep_for` 和 `std::this_thread::sleep_until` 在线程内部停顿一会

```cpp
#include <thread>
#include <iostream>
#include <chrono>

using namespace std::chrono;

void pausable() {
    // sleep 500毫秒
    std::this_thread::sleep_for(milliseconds(500));
    // sleep 到指定时间点
    std::this_thread::sleep_until(system_clock::now() + milliseconds(500));
}

int main() {
    std::thread thread(pausable);
    thread.join();

    return 0;
}
```

## 线程停止

一般情况下当线程函数执行完成后，线程自然停止；但 `std::thread` 实例析构时如果线程还在运行，会造成线程异常终止，可能会造成资源的泄露，尽量在析构前 join 一下，以确保线程成功结束

## 转移线程所有权

thread 是可移动的 (movable) 的，但不可复制 (copyable)，可以通过 `move()` 来改变线程的所有权，灵活的决定线程在什么时候 join 或者 detach

```cpp
thread t1(f1);
thread t3(move(t1));
// 意味着 thread 可以作为函数的返回类型，或者作为参数传递给函数，能够更为方便的管理线程
```

`std::thread` 被设计为只能由一个实例来维护线程状态，以及对线程进行操作。因此当发生赋值操作时，会发生线程所有权转移
```cpp
std::thread a(foo);
std::thread b;
b = a;

// 原来由 a 管理的线程改为由 b 管理，b 不再指向任何线程(相当于执行了 detach 操作)
// 如果 b 原本指向了一个线程，那么这个线程会被终止掉

// 赋值函数
thread& operator=(thread&& _Other) noexcept
{	// move from _Other
    return (_Move_thread(_Other));
}
```

## 获取线程 ID

每个线程都有一个 id，但此处的 `get_id()` 与系统分配给线程的 ID 并不一是同一个东西

通过 thread 的实例调用 `get_id()` 直接获取

在当前线程上调用 `this_thread::get_id()` 获取

想取得系统分配的线程ID，可以调用 `native_handle()` 函数

## 让出时间片

`std::this_thread::yield()` 将当前线程所抢到的 CPU 时间片让给其他线程，等到其他线程使用完时间片后，再由操作系统调度，当前线程再和其他线程一起开始抢 CPU 时间片