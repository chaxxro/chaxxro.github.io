# Bitmap

```
// 对 key 所储存的字符串值，设置或清除指定偏移量上的位
SETBTI key offset value
// 当 key 不存在时，自动生成一个新的字符串值

GETBIT key offset
// 当 offset 比字符串值的长度大，或者 key 不存在时，返回 0

// 返回 1 的数量
GETCOUNT key [start] [end]
// key 不存在则为 0

// 返回第一个值为 bit 的位置
BITPOS key bit [start] [end]

// 对多个 key 做并、或、异或、非计算
BITOP AND|OR|XOR|NOT dst key1 key2...
```