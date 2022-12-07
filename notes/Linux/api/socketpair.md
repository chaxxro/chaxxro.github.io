# socketpair

`socketpair` 是一对互相连接的 socket，相当于服务端和客户端的两个端点，每个端点都可以读写数据

```cpp
int socketpair(int domain, int type, int protocol, int sv[2]);
```