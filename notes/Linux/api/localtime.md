# localtime

根据本地时区信息将 `time` 函数获取的 UTC 时间调整为为本地时间，并将具体的时间信息填充到 `tm` 结构体之中

```cpp
struct tm {
  int tm_sec;         /* seconds */
  int tm_min;         /* minutes */
  int tm_hour;        /* hours */
  int tm_mday;        /* day of the month */
  int tm_mon;         /* month */
  int tm_year;        /* year */
  int tm_wday;        /* day of the week */
  int tm_yday;        /* day in the year */
  int tm_isdst;       /* daylight saving time */
};

struct tm * localtime (const time_t *t);
```

## 线程安全分析

```cpp
struct tm _tmbuf;
struct tm * localtime (const time_t *t);
{
  return __tz_convert (t, 1, &_tmbuf);
}
```

- `__tz_convert` 使用的是一个 `static` 变量的 `tzset_lock` 全局锁

- `__tz_convert` 返回的是入参 `&_tmbuf`，由于使用直接返回的是一个全局变量，所以不是线程安全的

- `localtime` 与 `localtime_r` 这两个函数都不是信号安全的，如果在信号处理函数中使用，就要考虑到死锁的情况，比如，程序调用 `localtime_r`，加锁后信号发生，信号处理函数中也调用 `localtime_r` 的话，会因为获取不到锁所以一直阻塞