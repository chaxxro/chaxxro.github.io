---
toc:
  enable: true
  number: false
  max_depth: 3
title: unique_lock
date: 2023-05-29 21:22:13
tags: cpp
categories: cpp
---

`lock_guard` 提供了简单上锁、解锁操作，但当需要更灵活的操作时便无能为力了

`unique_lock` 拥有对 `mutex` 的所有权，一但初始化了 `unique_lock`，其就接管了该 `mutex`，在 `unique_lock` 结束生命周期前（析构前），其它地方就不要再直接使用该 `mutex` 了

```cpp
template <class Mutex>
class unique_lock
{
public:
    typedef Mutex mutex_type;
    // 空unique_lock对象
    unique_lock() noexcept;
    // 管理m, 并调用m.lock进行上锁，如果m已被其它线程锁定，由该构造了函数会阻塞。
    explicit unique_lock(mutex_type& m);
    // 仅管理m，构造函数中不对m上锁。可以在初始化后调用lock, try_lock, try_lock_xxx系列进行上锁。
    unique_lock(mutex_type& m, defer_lock_t) noexcept;
    // 管理m, 并调用m.try_lock，上锁不成功不会阻塞当前线程
    unique_lock(mutex_type& m, try_to_lock_t);
    // 管理m, 该函数假设m已经被当前线程锁定，不再尝试上锁。
    unique_lock(mutex_type& m, adopt_lock_t);
    // 管理m, 并调用m.try_lock_unitil函数进行加锁
    template <class Clock, class Duration>
        unique_lock(mutex_type& m, const chrono::time_point<Clock, Duration>& abs_time);
    // 管理m，并调用m.try_lock_for函数进行加锁
    template <class Rep, class Period>
        unique_lock(mutex_type& m, const chrono::duration<Rep, Period>& rel_time);
    // 析构，如果此前成功加锁(或通过adopt_lock_t进行构造)，并且对mutex拥有所有权，则解锁mutex
    ~unique_lock();

    // 禁止拷贝操作
    unique_lock(unique_lock const&) = delete;
    unique_lock& operator=(unique_lock const&) = delete;

    // 支持move语义
    unique_lock(unique_lock&& u) noexcept;
    unique_lock& operator=(unique_lock&& u) noexcept;

    void lock();
    bool try_lock();

    template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
    template <class Clock, class Duration>
        bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);

    // 显示式解锁，该函数调用后，除非再次调用lock系列函数进行上锁，否则析构中不再进行解锁
    void unlock();

    // 与另一个unique_lock交换所有权
    void swap(unique_lock& u) noexcept;
    // 返回当前管理的mutex对象的指针，并释放所有权
    mutex_type* release() noexcept;

    // 当前实例是否获得了锁
    bool owns_lock() const noexcept;
    // 同owns_lock
    explicit operator bool () const noexcept;
    // 返回mutex指针，便于开发人员进行更灵活的操作
    // 注意：此时mutex的所有权仍归unique_lock所有，因此不要对mutex进行加锁、解锁操作
    mutex_type* mutex() const noexcept;
};
```

```cpp
std::mutex mtx;           // mutex for critical section
std::once_flag flag;

void print_block (int n, char c)
 {
    //unique_lock有多组构造函数, 这里std::defer_lock不设置锁状态
    std::unique_lock<std::mutex> my_lock (mtx, std::defer_lock);
    //尝试加锁, 如果加锁成功则执行
    //(适合定时执行一个job的场景, 一个线程执行就可以, 可以用更新时间戳辅助)
    if(my_lock.try_lock())
    {
        for (int i=0; i<n; ++i)
            std::cout << c;
        std::cout << '\n';
    }
}

void run_one(int &n)
{
    std::call_once(flag, [&n]{n=n+1;}); //只执行一次, 适合延迟加载; 多线程static变量情况
}

int main () 
{
    std::vector<std::thread> ver;
    int num = 0;
    for (auto i = 0; i < 10; ++i)
    {
        ver.emplace_back(print_block,50,'*');
        ver.emplace_back(run_one, std::ref(num));
    }

    for (auto &t : ver)
    {
        t.join();
    }
    std::cout << num << std::endl;
    return 0;
}
```