# fcntl

`fcntl` 函数可以改变或者查看已打开文件的性质

```cpp
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd);
int fcntl(int fd, int cmd, long arg);
int fcntl(int fd, int cmd, struct flock *lock); 
//返回值：如果成功则依赖于 cmd，出错则返回 -1
```

`fcntl` 有 5 中功能

- 复制一个现有文件描述符 `cmd = F_DUPFD`

- 获取/设置文件描述符标记 `cmd = F_SETFD / F_GETFD`

- 获取/设置文件状态标记 `cmd = F_SETFL / F_GETFL`

- 获取/设置异步I/O所有权 `cmd = F_SETOWN / F_GETOWN`
 
- 获取/设置记录锁 `cmd = F_SETLK / F_GETLK / F_SETLKW` 

```cpp
// 将 socket 设置为非阻塞
int flag = fcntl(socket_fd, F_GETFL, 0);
fcntl(socket_fd, F_SETFL, flag | O_NONBLOCK);
// 将 socket 设置为阻塞
int flag = fcntl(socket_fd, F_GETFL, 0);
fcntl(socket_fd, F_SETFL, flag & ~O_NONBLOCK);
```