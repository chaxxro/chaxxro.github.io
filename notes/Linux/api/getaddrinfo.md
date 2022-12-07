# getaddrinfo

```cpp
int getaddrinfo(const char* node, const char* service,
                const struct addrinfo* hints,
                struct addrinfo** res);
// 成功返回 0。否则返回非 0
// 结果存储在 res 中

struct addrinfo {
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    socklen_t ai_addrlen;
    struct sockaddr* ai_addr;
    char* ai_canonname;
    struct addrinfo* ai_next;
}

// 释放 res
void freeaddrinfo(struct addrinfo* res);

struct addrinfo hints = {0};
hints.ai_flags = AI_CANONNAME;
hints.ai_family = family;
hints.ai_socktype = socktype;

struct addrinfo* res;
int n = getaddrinfo(host, service, &hints, &res);
if (n == 0) {
    freeaddr(res);
}
```