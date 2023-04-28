---
toc:
  enable: true
  number: false
  max_depth: 3
title: sds
date: 2023-04-28 21:30:54
tags:
categories:
---

Redis 构建了一种简单动态字符串的抽象类型，作为 Redis 默认字符串的底层结构

## 数据结构

```cpp
#define SDS_TYPE_5     0   // 000
#define SDS_TYPE_8     1   // 001
#define SDS_TYPE_16    2   // 010
#define SDS_TYPE_32    3   // 011
#define SDS_TYPE_64    4   // 100
// 所有 sds 类型的 flags 低三位表示类型
struct __attribute__ ((__packed__)) sdshdr5 {
    // 高五位表示长度，长度最大 31
    unsigned char flags;
    char buf[];  // 柔性数组
}
struct __attribute__ ((__packed__)) sdshdr8 {
    // 长度范围 32 ～ 255
    uint8_t len;
    uint8_t alloc;
    unsigned char flags;
    char buf[];  // 柔性数组
}
struct __attribute__ ((__packed__)) sdshdr16 {
    // 长度范围 256 ～ 65535
    uint16_t len;
    uint16_t alloc;
    unsigned char flags;
    char buf[];  // 柔性数组
}
struct __attribute__ ((__packed__)) sdshdr32 {
    uint32_t len;
    uint32_t alloc;
    unsigned char flags;
    char buf[];  // 柔性数组
}
struct __attribute__ ((__packed__)) sdshdr64 {
    uint32_t len;
    uint32_t alloc;
    unsigned char flags;
    char buf[];  // 柔性数组
}
// __attribute__ 设置属性
// __packed__ 取消内存对齐
```

- `len` 当前已使用的字节数，不包括 `\0`

- `alloc` 总共分配的字节数量，不包括 `\0`

- `flags` 低三位表示当前字节数组的属性，是 `SDS_TYPE_5` 还是 `SDS_TYPE_8` 等

- `buf` 数组，用于保存字符串，包括结尾空白符 `\0`

## 选择依据

根据所需长度返回 `sds::flags`

```cpp

static inline char sdsReqType(size_t len) {
    if (len < 1 << 5) . // 32
        return SDS_TYPE_5;
    if (len < 1 << 8)   // 258
        return SDS_TYPE_8;
    if (len < 1 << 16)  // 65536
        return SDS_TYPE_16;
#if (LONG_MAX == LLONG_MAX)
    if (len < 1ll << 32)
        return SDS_TYPE_32;
    return SDS_TYPE_64;
#else
    return SDS_TYPE_5;
#endif
}
```

## 获取 sds 长度

```cpp
typedef char* sds;

#define SDS_TYPE_BITS 3
#define SDS_TYPE_MASK  7   // 111
#define SDS_TYPE_5_LEN(f) ((f)>>SDS_TYPE_BITS)

// 因为 buf 是柔性数组，所以可以这么根据 buf 获取首地址
#define SDS_HDR_VAR(T, s) \
    struct sdshdr##T* sh = (void*)((s) - (sizeof(struct sdshdr##T)));
#define SDS_HDR(T, s) \
        ((struct sdshdr##T*)((s)- (sizeof(struct sdshdr##T))))

static inline size_t sdslen(cosnt sds s) {
    // sdshdr* 取消了内存对齐，因此这里可以直接取到 flags
    unsigned char flags = s[-1];
    switch (flags & SDS_TYPE_MASK) {
        case SDS_TYPE_5:
            // 高五位表示长度
            return SDS_TYPE_5_LEN(flags);
        case SDS_TYPE_8:
            return SDS_HDR(8, s)->len;
        case SDS_TYPE_16:
            return SDS_HDR(16, s)->len;
        case SDS_TYPE_32:
            return SDS_HDR(32, s)->len;
        case SDS_TYPE_64:
            return SDS_HDR(64, s)->len;
    }
    return 0;
}
```

## 扩容机制

1. 判断预留空间是否满足要求，若满足要求则不扩容

2. 计算新 sds 占用空间大小，若小于 1M 则进行所需大小 2 倍的扩容

3. 若新空间不小于 1M 时每次扩容 1M

4. 根据新长度重新计算 sds 类型，若新类型与就类型一致则进行 `s_realloc` 动态扩容，若不一致则重新申请空构造新对象，并释放久对象

```cpp
#define SDS_MAX_PREALLOC (1024 * 1024)
sds sdsMakeRoomFor(sds s, size_t addlen) {
    void *sh, *newsh;
    size_t avail = sdsavail(s);  // 当前可用空间
    size_t len, newlen, reqlen;
    char type, oldtype = s[-1] & SDS_TYPE_MASK;
    int hdrlen;
    size_t usable;

    if (avail >= addlen) return s;
    len = sdslen(s);  // 当前长度
    sh = (char*)s - sdsHdrSize(oldtype);  // 旧对象指针
    reqlen = newlen = len + addlen;  // 期望长度
    assert(newlen > len);  // catch size_t overflow

    if (newlen < SDS_MAX_PREALLOC)
        newlen *= 2;
    else
        newlen += SDS_MAX_PREALLOC;

    type = sdsReqType(newlen);  // 期望对象类型
    if (type == SDS_TYPE_5) type = SDS_TYPE_8;

    hdrlen = sdsHdrSize(type);  // 期望对象所占内存大小
    assert(hdrlen + newlen + 1 > reqlen);  // catch size_t overflow
    if (oldtype == type) {
        newsh = s_realloc_usable(sh, hdrlen + newlen + 1, &usable);
        if (newsh == nullptr) return nullptr;
        s = (char*)newsh + hdrlen;
    } else {
        newsh = s_malloc_usable(hdrlen + newlen + 1, &usable);
        if (newsh == nullptr) return nullptr;
        memcpy((char*)newsh + hdrlen, s, len + 1);
        s_free(sh);
        s = (char*)newsh + hdflen;
        s[-1] = type;
        sdssetlen(s, len);
    }
    usable = usable - hdrlen - 1;
    if (usable > sdsTypeMaxSize(type))
        usable = sdsTypeMaxSize(type);
    sdssetalloc(s, usable);
    return s;
}
```

每次新开空间都会额外多加 1 字节，是为了保证最后可以写入一个 `\0`

## 与 C 字符串区别

- 获取字符串长度时间复杂度 O(1)

- 杜绝缓冲区溢出，C 字符串每次增长都需要重新分配新的内存，每次缩短如果不重新分配内存会导致内存浪费

- 惰性空间释放

- 二进制安全，C 字符串必须符合某种编码，并且除字符串末尾外不能包涵空白字符，否者空白字符会被当作字符结尾，导致只能保存文本数据，不能保存图片视频等二进制数据，SDS 是通过 `len` 字段判断字符串结束

- 兼容性，SDS 的 API 都是二进制安全的，但也遵循 C 字符串以空白结尾的惯例