# ioctl

当一个非监听 socket 可读时，使用 `ioctl` 可以获取接受缓冲区已有多少数据可读

```cpp
int ioctl(int d, int request, ...)
```