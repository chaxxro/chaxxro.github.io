# 信号量

信号量代表一定的资源数量，可以根据当前资源的数量按需唤醒指定数量的资源消费者线程

信号量表示资源的数量，对应的变量是一个整型（sem）变量，还有两个原子操作的系统调用函数来控
制信号量，分别是：P 操作，将 sem 减 1，相减后，如果 sem < 0，则进程/线程进入阻塞等待，
否则继续，表明 P 操作可能会阻塞；V 操作：将 sem 加 1，相加后，如果 sem <= 0，唤醒一个等待
中的进程/线程，表明 V 操作不会阻塞

P 操作是用在进入临界区之前，V 操作是用在离开临界区之后，这两个操作是必须成对出现的

PV 操作的函数是由操作系统管理和实现的，所以操作系统已经使得执行 PV 函数时是具有原子性的

## 初始化

```cpp
int sem_init(sem_t* sem, int pshared, unsigned int value);
```

- `sem` 传入需要初始化的信号量

- `pshared` 表示信号量是否可以被共享，0 表示只能被同一进程的线程共享，非 0 表示可以在多个进程间共享

- `value` 表示信号量初始状态的资源数量

## 销毁

```cpp
int sem_destroy(sem_t* sem);
```

销毁指定信号量

## 获取信号量

```cpp
int sem_wait(sem_t* sem);

int sem_trywait(sem_t* sem);

int sem_timewait(sem_t* sem, const struct timespec* abs_timeout);

struct timespec {
    time_t tv_sec;  // 秒
    long tv_nsec;  // 纳秒，取值 [0, 999999999]
}
```

当信号量的资源计数为 0 时， `sem_wait` 会阻塞调用线程，直到信号量的资源计数大于 0 时被唤醒，获得信号量后资源计数将减 1，然后立即返回

`sem_trywait` 是 `sem_wait` 的非阻塞版本，当信号量资源计数为 0 时将立即返回 -1， `errno` 为 `EAGAIN`

`sem_timewait` 是带等待时间的版本，等待时间由 `abs_timeout` 设置，超时后返回 -1，`errno` 为 `ETIMEOUT`，`abs_timeout` 不能为 `nullptr`，`abs_timeout` 是绝对时间

`sem_wait`、`sem_trywait` 和 `sem_timewait` 可以被信号中断，信号中断后立即返回 -1，`errno` 为 `EINTR`

## 释放信号量

```cpp
int sem_post(sem_t* sem);
```

`sem_post` 用于将信号量的资源计数加 1，然后释放信号量