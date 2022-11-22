# 哈希表

## 数据结构

```cpp
typedef struct dictEntry {
    void *key;
    union {
        void *val;
        uint64_t u64;
        int64_t s64;
        double d;
    } v;
    struct dictEntry *next;  // 多个哈希值相同的 key 组成链表
} dictEntry;

// 一些哈希表要用到的函数
typedef struct dictType {
    // 哈希函数
    uint64_t (*hashFunction)(const void *key);
    // 复制键函数
    void *(*keyDup)(void *privdata, const void *key);
    // 复制值函数
    void *(*valDup)(void *privdata, const void *obj);
    // 对比键函数
    int (*keyCompare)(void *privdata, const void *key1, const void *key2);
    // 销毁键函数
    void (*keyDestructor)(void *privdata, void *key);
    // 销毁值函数
    void (*valDestructor)(void *privdata, void *obj);
    // 判断是否需要 rehash
    int (*expandAllowed)(size_t moreMem, double usedRatio);
} dictType;

// 实际的哈希表
typedef struct dictht {
    dictEntry **table;
    unsigned long size;  // 默认值 0
    unsigned long sizemask;  // 哈希表大小掩码，用于计算索引，默认值 0
    unsigned long used;  // 已有节点数，包括 bucket 中的节点，默认值 0
} dictht;

// 暴露的结构
typedef struct dict {
    dictType *type;
    void *privdata;  // 私有数据
    dictht ht[2];  // 两个哈希表用于渐进 rehash
    long rehashidx; // -1 表示没有在进行 rehash，默认值 -1
                    // >= 0 时表示 dictht.table 中的下标
    int16_t pauserehash; // >0 表示 rehash 暂停中，<0 表示错误，默认值 0
} dict;
```

## Add

```cpp
int dictAdd(dict *d, void *key, void *val)
{
    dictEntry *entry = dictAddRaw(d,key,NULL);

    if (!entry) return DICT_ERR;
    dictSetVal(d, entry, val);
    return DICT_OK;
}

/* 
 * dictAddRaw 插入 entry 但并不设置值，而是将 dictEntry 返回给调用方由调用方设置值
 * 返回 dictEntry 而不设置值，主要是因为不想在存储 value 的指针
 * 返回值：
 * 当 key 已存在时，返回 null，并且如果 *existing 非空的话则用 *existing 覆盖
 * 当 key 不存在时，返回插入的 entry
 */
dictEntry *dictAddRaw(dict *d, void *key, dictEntry **existing)
{
    long index;
    dictEntry *entry;
    dictht *ht;

    // 顺带 rehash 一个 bucket
    if (dictIsRehashing(d)) _dictRehashStep(d);

    /* Get the index of the new element, or -1 if
     * the element already exists. */
    if ((index = _dictKeyIndex(d, key, dictHashKey(d,key), existing)) == -1)
        return NULL;

    /* Allocate the memory and store the new entry.
     * Insert the element in top, with the assumption that in a database
     * system it is more likely that recently added entries are accessed
     * more frequently. */
    ht = dictIsRehashing(d) ? &d->ht[1] : &d->ht[0];
    entry = zmalloc(sizeof(*entry));
    entry->next = ht->table[index];
    ht->table[index] = entry;
    ht->used++;

    /* Set the hash entry fields. */
    dictSetKey(d, entry, key);
    return entry;
}

/* 返回 key 对应的 dict.dictht.dictEntry 下标
 * 如果 key 对应下标已存在，即哈希冲突，返回 -1
 * and the optional output parameter may be filled.
 *
 * 如果正在进行 rehash，则计算 key 在新 dictht 中的下标
 */
static long _dictKeyIndex(dict *d, const void *key, uint64_t hash, dictEntry **existing)
{
    unsigned long idx, table;
    dictEntry *he;
    if (existing) *existing = NULL;

    /* Expand the hash table if needed */
    if (_dictExpandIfNeeded(d) == DICT_ERR)
        return -1;
    for (table = 0; table <= 1; table++) {
        idx = hash & d->ht[table].sizemask;
        /* Search if this slot does not already contain the given key */
        he = d->ht[table].table[idx];
        while(he) {
            if (key==he->key || dictCompareKeys(d, key, he->key)) {
                if (existing) *existing = he;
                return -1;
            }
            he = he->next;
        }
        if (!dictIsRehashing(d)) break;
    }
    return idx;
}
```

## rehash

```cpp
// 通过 dict.rehashidx 判断是否在 rehash
#define dictIsRehashing(d) ((d)->rehashidx != -1)

static void _dictRehashStep(dict* d) {
    if (d->pauserehash == 0) dictRehash(d, 1);
}

/* 执行渐进式 rehash 迁移 n 个元素
 * 当仍有 key 需要迁移时返回 1，否则返回 0
 *
 * 考虑到不要阻塞太长时间，所以该步骤只会最多访问 N*10 个空 bucket
 */
int dictRehash(dict *d, int n) {
    int empty_visits = n*10;
    if (!dictIsRehashing(d)) return 0;

    while(n-- && d->ht[0].used != 0) {
        dictEntry *de, *nextde;

        assert(d->ht[0].size > (unsigned long)d->rehashidx);
        while(d->ht[0].table[d->rehashidx] == NULL) {
            d->rehashidx++;
            // 最多访问 10*n 个空 bucket
            if (--empty_visits == 0) return 1;
        }
        de = d->ht[0].table[d->rehashidx];
        while(de) {
            uint64_t h;

            nextde = de->next;
            // 计算 rehash 后的 key
            h = dictHashKey(d, de->key) & d->ht[1].sizemask;
            // 将 ht[0] 的数据放入 ht[1] 中
            de->next = d->ht[1].table[h];
            d->ht[1].table[h] = de;
            d->ht[0].used--;
            d->ht[1].used++;
            de = nextde;
        }
        d->ht[0].table[d->rehashidx] = NULL;
        d->rehashidx++;
    }

    // 当 ht[0] 全部迁移完成，交换 ht[0] 和 ht[1]
    if (d->ht[0].used == 0) {
        zfree(d->ht[0].table);
        d->ht[0] = d->ht[1];
        _dictReset(&d->ht[1]);
        d->rehashidx = -1;
        return 0;
    }

    /* More to rehash... */
    return 1;
}
```