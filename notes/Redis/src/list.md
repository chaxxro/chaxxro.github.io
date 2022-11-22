# 链表

## 基础

```
// 双向链表
typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

// 迭代器指向下一个节点
typedef struct listIter {
    listNode *next;
    int direction;
} listIter;

// 双向无环
typedef struct list {
    listNode *head;
    listNode *tail;
    void *(*dup)(void *ptr);
    void (*free)(void *ptr);
    int (*match)(void *ptr, void *key);
    unsigned long len;
} list;
```