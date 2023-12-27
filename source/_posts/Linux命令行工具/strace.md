---
toc:
  enable: true
  number: false
  max_depth: 3
title: post
date: 2023-12-25 21:44:04
tags: 命令行工具
categories: Linux 命令行
---

跟踪进程系统调用和解决库依赖问题

```sh
strace [-ACdffhikqqrtttTvVwxxyyzZ] [-I n] [-b execve] [-e expr]... [-O overhead] [-S sortby] [-U columns] [-a column] [-o file] [-s strsize]
              [-X format] [-P path]... [-p pid]... [--seccomp-bpf] { -p pid | [-DDD] [-E var[=val]]... [-u username] command [args] }

-c 统计每一系统调用的所执行的时间、次数和出错的次数等
-d 输出 strace 本身的标准错误调试信息
-f 跟踪由 fork 调用所产生的子进程
--output-separately 多个进程的 strace 分开输出
-ff 等同于 -f + --output-separately
-i 输出系统调用的入口指针
-t 在输出中的每一行前加上时间信息
-tt 在输出中的每一行前加上微秒级时间信息
-T 显示每一调用所耗的时间
-v 输出所有的系统调用
-x 以十六进制形式输出非标准字符串
-xx 所有字符串以十六进制形式输出

-e expr 指定一个表达式，用来控制如何跟踪.格式如下 [qualifier=][!]value1[,value2]...
qualifier 只能是 trace、abbrev、verboseraw、signal、read、write，默认是 trace
value 是用来限定的符号或数字，有两个特殊的符号 all 和 none
感叹号是否定符号
-eopen 等价于 -e trace=open，表示只跟踪 open 调用，-e trace!=open表示跟踪除了 open 以外的其他调用
-e trace=open,close,rean,write 表示只跟踪这四个系统调用
-e trace=file 只跟踪有关文件操作的系统调用
-e trace=process 只跟踪有关进程控制的系统调用
-e trace=network 跟踪与网络有关的所有系统调用
-e strace=signal 跟踪所有与系统信号有关的系统调用
-e trace=ipc 跟踪所有与进程通讯有关的系统调用
-e abbrev=set 设定 strace 输出的系统调用的结果集，-v 等于 abbrev=none，默认为abbrev=all
-e raw=set 将指定的系统调用的参数以十六进制显示
-e signal=set 指定跟踪的系统信号，默认为 all，如 signal=!SIGIO
-e read=set 输入从指定文件中读取，如 -e read=3,5
-e write=set 输出写入到指定文件中

-o filename 将strace的输出写入文件
-p pid 跟踪指定的进程pid
-u username 以 username 的 UID 和 GID 执行被跟踪的命令
```