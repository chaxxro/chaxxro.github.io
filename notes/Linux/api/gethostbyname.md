# gethostbyname

将域名转换成 ip

```cpp
struct hostent* gethostbyname(const char* name);

struct hostent {
    char* h_name;        // 地址的正式名称
    char** h_aliases;    // 地址的预备名称指针
    int h_addrtype;      // 地址类型，通常是 AF_INE
    int h_length;        // 地址长度，以字节为单位
    char** h_addr_list   // 主机网络地址指针，网络字节序
};
#define h_addr h_addr_list[0]

auto pHostent = gethostbyname("www.baidu.com");
if (!pHostent) return;
struct sockaddr_in addr = {0};
addr.sin_addr.s_addr = *((unsigned long*)pHostent->h_addr_list[0]);
```

`h_addr_list[0]` 虽然是个 `char*`，但实际是 `uint32_t*`，因为 IP 地址是用 32bit 整数表示

`gethostbyname` 是不可重入函数，可以使用 `gethostbyname_r` 替代

`gethostbyname` 在解析域名时会阻塞当前执行线程，直到返回结果

## 错误码

使用 `gethostbyname` 出错时，不能使用 `errno`，应该使用 `h_errno`，或者调用 `herror` 函数

```cpp
void herror(const char* s)
```