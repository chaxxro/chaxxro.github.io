---
toc:
  enable: true
  number: false
  max_depth: 3
title: RedisObject
date: 2023-04-20 21:01:29
tags: redis
categories: redis
---

Redis 键值对中的每一个值都是用 `redisObject` 保存的

## 基本对象结构

因为 Redis 的数据类型有很多，而且不同数据类型都有些相同的元数据要记录（比如最后一次访问的时间、被引用的次数等），所以 Redis 会用一个 `redisObject` 结构体来统一记录这些元数据，同时指向实际数据

```c
/* The actual Redis Object */
#define OBJ_STRING 0    /* String object. */
#define OBJ_LIST 1      /* List object. */
#define OBJ_SET 2       /* Set object. */
#define OBJ_ZSET 3      /* Sorted set object. */
#define OBJ_HASH 4      /* Hash object. */

#define OBJ_MODULE 5    /* Module object. */
#define OBJ_STREAM 6    /* Stream object. */

typedef struct redisObject {
    unsigned type:4; // 0 ~ 15
    unsigned encoding:4; // 0 ~ 15
    /* LRU time (relative to global lru_clock) or
     * LFU data (least significant 8 bits frequency
     * and most significant 16 bits access time). 
     * #define LRU_BITS 24
     */
    unsigned lru:LRU_BITS;  // 最近使用时的时间戳
    int refcount;
    void *ptr;
} robj;
```

一个 `redisObject` 占 16 个字节，元数据占 8 个字节，实际数据指针占 8 个字节

`encoding` 记录了对象使用的底层编码方式，不同的场景同一类型对象可能使用不同的底层编码方式

`lru` 记录了这个对象最后一次被访问的时间，用于淘汰过期的键值对

`refcount` 记录了对象的引用计数

`ptr` 指向数据的指针

{% asset_img 01.png %}

## 各类型对应编码方式


```c
/* Objects encoding. Some kind of objects like Strings and Hashes can be
 * internally represented in multiple ways. The 'encoding' field of the object
 * is set to one of this fields for this object. */
#define OBJ_ENCODING_RAW 0     /* Raw representation */
#define OBJ_ENCODING_INT 1     /* Encoded as integer */
#define OBJ_ENCODING_HT 2      /* Encoded as hash table */
#define OBJ_ENCODING_ZIPMAP 3  /* Encoded as zipmap */
#define OBJ_ENCODING_LINKEDLIST 4 /* No longer used: old list encoding. */
#define OBJ_ENCODING_ZIPLIST 5 /* Encoded as ziplist */
#define OBJ_ENCODING_INTSET 6  /* Encoded as intset */
#define OBJ_ENCODING_SKIPLIST 7  /* Encoded as skiplist */
#define OBJ_ENCODING_EMBSTR 8  /* Embedded sds string encoding */
#define OBJ_ENCODING_QUICKLIST 9 /* Encoded as linked list of ziplists */
#define OBJ_ENCODING_STREAM 10 /* Encoded as a radix tree of listpacks */
```

{% asset_img 02.png %}

String 类型的底层实现只有一种数据结构，也就是简单动态字符串

List、Hash、Set 和 Sorted Set 这四种数据类型，都有两种底层实现结构，这四种类型为集合类型，特点是一个键对应一个集合的数据

{% asset_img 03.png %}