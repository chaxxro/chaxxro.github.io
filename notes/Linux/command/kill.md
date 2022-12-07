# kill

将指定的信号发送到指定的进程或进程组，如果未指定信号，则发送 TERM 信号

```
kill [-s signal] pid

kill 12345 杀死进程

kill -KILL 123456 强制杀死进程

kill -9 123456
```

|编号|名称|描述
|-|-|-|
1|HUP|挂起
2|INT|中断
3|QUIT|结束运行
9|KILL|无条件终止
11|SEGV|段错误
15|TERM|尽可能终止
17|STOP|无条件停止运行，但不终止
18|TSTP|停止或暂停，但继续在后台运行
19|CONT|在 STOP 或 TSTP 之后恢复