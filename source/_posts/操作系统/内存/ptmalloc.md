---
toc:
  enable: true
  number: false
  max_depth: 3
title: ptmalloc
date: 2024-01-23 20:23:26
tags: 操作系统
categories: 内存管理
---

glibc 中的 ptmalloc

## 分配区 arena

在 ptmalloc 中，使用分配区 arena 管理从操作系统中批量申请来的内存

在 ptmalloc 中存在一个全局的主分配区，是用静态变量的方式定义的

```cpp
static struct malloc_state main_arena;

struct malloc_state {
 // 锁，用来解决在多线程分配时的竞争问题
 mutex_t mutex;

 // 分配区下管理内存的各种数据结构
 /* Fastbins */
 mfastbinptr      fastbins[NFASTBINS];

 /* Base of the topmost chunk -- not otherwise kept in a bin */
 mchunkptr        top;

 /* The remainder from the most recent split of a small request */
 mchunkptr        last_remainder;

 /* smallbins、largetbins、unsortedbins */
 mchunkptr        bins[NBINS * 2];  // 128 * 2

 /* Bitmap of bins */
 unsigned int     binmap[BINMAPSIZE];
 ...

 /* Linked list */
 struct malloc_state *next;  // 把所有的分配区都以一个链表组织了起来，方便后面的遍历
}
```

对于每一个进程而言，只有一个主分配区，可能存在多个非主分配区，ptmalloc 会根据系统对分配区的争用情况动态增加非主分配区的数量，主分配区与非主分配区用环形链表进行管理

多线程在操作一个分配区的时候需要加锁，在线程比较多的时候在锁上浪费的开销会比较多。为了降低锁开销，ptmalloc 支持多个分配区。这样在单个分配区上锁的竞争开销就会小很多

主分配区可以访问进程的 heap 区域和 mmap 映射区域，也就是说主分配区可以使用 `sbrk` 和 `mmap` 向操作系统申请内存，而非主分配区域只能访问进程的 `mmap` 映射区域

## 内存块 chunk

在每个 arena 中，最基本的内存分配的单位是 malloc_chunk，简称 chunk，包含 header 和 body 两部分

```cpp
struct malloc_chunk {
 INTERNAL_SIZE_T      prev_size;  /* Size of previous chunk (if free).  */
 INTERNAL_SIZE_T      size;       /* Size in bytes, including overhead. */

 struct malloc_chunk* fd;         /* double links -- used only if free. */
 struct malloc_chunk* bk;

 /* Only used for large blocks: pointer to next larger size.  */
 struct malloc_chunk* fd_nextsize; /* double links -- used only if free. */
 struct malloc_chunk* bk_nextsize;
};
```

调用 `malloc` 申请内存时，分配器都会分配一个大小合适的 chunk，并把 body 部分的 user data 的地址返回

调用 `free` 释放内存时，其对应的 chunk 对象其实并不会归还给内核，而是由 glibc 又组织管理起来。body 部分的 fd、bk 字段分别是指向上一个和下一个空闲的 chunk，用来当双向链表指针来使用。chunk 在使用的时候是没有这两个字段的，这块内存在不同场景下的用途不同

## 空闲内存块链表 bins

glibc 会将相似大小的空闲内存块 chunk 都串起来，这样等下次用户再来分配的时候，先找到链表，然后就可以从链表中取出一个元素快速分配。这样的一个链表被称为一个 bin

ptmalloc 中根据管理的内存块的大小，总共有 fastbins、smallbins、largebins 和 unsortedbins 四类

### fastbins 

fastbins 用来管理尺寸最小空闲内存块的链表，它有多个链表，每个 bin 链表管理的都是固定大小的 chunk 内存块。在 64 位系统下，每个链表管理的 chunk 元素大小分别是 32 字节、48 字节、...、128 字节等不同的大小

用户的应用程序中绝大多数的内存分配是小内存，所以这组 bin 是用于提高小内存的分配效率的

### smallbins

smallbins 数组总共有 64 个链表指针，同一个 small bin 中的 chunk 具有相同的大小

在 64 位系统上，两个相邻的 small bin 中的 chunk 大小相差 16 字节

### largebins

largebins 管理的内存是 1024 起，且每两个相邻的 largebin 之间管理的内存块大小不再是固定的等差数列

### unsortedbins

unsortedbins 管理的内存块是被当做缓存区来用的

当用户释放一个堆块之后，会先进入 unsortedbin。再次分配堆块时，ptmalloc 会优先检查这个链表中是否存在合适的堆块，如果找到了，就直接返回给用户(这个过程可能会对 unsortedbin 中的堆块进行切割)。若没有找到合适的，系统也会顺带清空这个链表上的元素，把它放到合适的 smallbin 或者 large bin 中

## malloc 的工作过程

当用户要分配内存的时候，malloc 函数就可以根据其大小，从合适的 bins 中查找合适的 chunk

当用户用完需要释放的时候，glibc 再根据其内存块大小，放到合适的 bin 下管理起来。下次再给用户申请时备用

当需要申请小内存块，但是没有大小合适的时候，会将大的 chunk 拆成多个小 chunk。如果申请大内存块的时候，而系统中又存在大量的小 chunk 的时候，又会发生合并，以降低碎片率

1. 如果申请字节数小于 fast bins 管理的内存块最大字节数，则尝试从 fastbins 中申请内存，申请成功就返回

2. 如果申请字节数小于 small bins 管理的内存，则尝试从 smallbins 中申请内存，申请成功就返回

3. 尝试从 unsorted bins 中申请内存，申请成功就返回

4. 尝试从 large bins 中申请内存，申请成功就返回

5. 尝试从 top chunk 中申请内存并返回

6. 向操作系统申请内存

## malloc 多线程工作过程

线程先查看私有变量中是否已经存在有一个分配区。如果存在则尝试对对应的分配区加锁。如果加锁成功则使用这个分配区分配内存。如果失败则搜索循环链表试图获得一个没有加锁的分配区来分配内存。如果所有的分配区都已经加锁了，那么 `malloc` 会开辟一个新的分配区，把该分配区添加到循环链表中并加锁，使用这个分配区进行分配内存操作

在释放操作中，线程同样试图获得待释放内存块所在的分配区的锁，如果该分配区正在被别的线程使用，则需要等待直到其他线程释放该分配区的互斥锁之后才可以进行释放操作

非主分配区的数量一旦增加，就不会再减少