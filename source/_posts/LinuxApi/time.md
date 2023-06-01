---
toc:
  enable: true
  number: false
  max_depth: 3
title: time
date: 2023-05-31 21:26:23
tags: LinuxApi
categories: LinuxApi
---

## time_t

```cpp
#include <time.h>
typedef long time_t  

struct tm{    
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
    long int tm_gmtoff;   
    const char* tm_zone;  
};

// 如果 t 并非空指针的话，此函数也会将返回值存到 t 指针所指的内存
time_t time(time_t *t);
// 求差值
double difftime(time_t time1, time_t time0);
// 获取本地时间 tm
struct tm *localtime(const time_t *timer);
// 获取国际时间 tm
struct tm* gmtime( const time_t* p_time );
time_t mktime(struct tm * timeptr);
// 时区信息使用 timeptr 中的信息
char * asctime(const struct tm * timeptr);
// 一律使用本地时区
char * ctime(const time_t *timer);

/*
%a : 本第几天名称，缩写
%A : 本第几天名称，全称
%b : 月份名称，缩写
%B : 月份名称，全称
%c : 与ctime/asctime格式相同
%d : 本月第几日名称，由零算起
%H : 当天第几个小时，24小时制，由零算起
%I : 当天第几个小时，12小时制，由零算起
%j : 当年第几天，由零算起
%m : 当年第几月，由零算起
%M : 该小时的第几分，由零算起
%p : AM或PM
%S : 该分钟的第几秒，由零算起
%U : 当年第几，由第一个日开始计算
%W : 当年第几，由第一个一开始计算
%w : 当第几日，由零算起
%x : 当地日期
%X : 当地时间
%y : 两位数的年份
%Y : 四位数的年份
%Z : 时区名称的缩写
%% : %符号
*/
size_t strftime(char *str,size_t max,char *fmt,struct tm *tp);
```

## timeval

```cpp
#include "sys/time.h"
struct timeval  
{  
    __time_t tv_sec;        // 秒
    __suseconds_t tv_usec;  // 微秒
}; 

// 把时间信息存入 tv，当地时区信息则放到 tz
int gettimeofday(struct timeval*tv, struct timezone *tz);  
/*判断tvp是否填充*/  
#define       timerisset(tvp)  ((tvp)->tv_sec || (tvp)->tv_usec)   
/*tvp设置为0*/  
#define       timerclear(tvp) ((tvp)->tv_sec = (tvp)->tv_usec = 0)    
/*tvp比较，cmp不可为>=, <=*/  
#define       timercmp(tvp, uvp, cmp)   
              ((tvp)->tv_sec cmp (uvp)->tv_sec ||\   
               (tvp)->tv_sec == (uvp)->tv_sec &&\   
               (tvp)->tv_usec cmp (uvp)->tv_usec)   
/*result = a+b*/  
#define     timeradd(a, b, result)  
/*result = a-b*/  
#define     timersub(a, b, result) 
```

## timespec

```cpp
struct timespec  
{  
    long int tv_sec;    //秒
    long int tv_nsec;   //纳秒
}; 

long clock_gettime(clockid_t which_clock_id, struct timespec *tp);
/*
which_clock_id
CLOCK_REALTIME 系统实时时间
CLOCK_MONOTONIC 从系统启动这一刻起开始计时,
CLOCK_PROCESS_CPUTIME_ID 本进程到当前代码系统CPU花费的时间
CLOCK_THREAD_CPUTIME_ID 本线程到当前代码系统CPU花费的时间
*/
int timespec_get( struct timespec *ts, int base );
// base
#define TIME_UTC /* implementation-defined */
```

## clock_t

从进程开始到现在的时间

```cpp
clock_t clock()；
#define CLOCKS_PER_SEC
```