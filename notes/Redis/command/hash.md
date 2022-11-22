# Hash

```
// 将 hash 表中 filed 设置为 valude
HSET hash field value
// 如果给定的哈希表并不存在， 那么创建一个新的哈希表
// 如果 field 已经存在于哈希表中， 那么它的旧值将被新值覆盖

HGET hash field

HEXISTS hash field

HMSET hash field1 value1 fedld2 value2...
// 会覆盖已存在的 field

HMGET hash field1 field2...

// 哈希表不存在则创建
// field 存在则放弃执行
// field 不存在则执行
HSETNX hash field value

// 删除 hash 中的 field
HDEL hash field1 field2

// 获取 hash 表中 field 数量
HLEN hash

// 获取 hash 表中 field 对应的字符串长度
HSTRLEN hash field

// 为 hash 表中 field 的值加上增量
// 增量可以为负数
HINCRBY hash field num
HINCRBYFLOAT hash field num
// hash 不存在则新建
// field 不存在则初始化为 0

// 获取 hash 中所有的 field
HKEYS hash

// 获取 hash 中所有 value
HVALS hash

// 获取 hash 中所有 field-value
HGETALL hash
```