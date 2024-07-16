---
toc:
  enable: true
  number: false
  max_depth: 3
title: 大PB解析优化
date: 2024-07-16 16:26:44
tags: 问题分析
categories: 问题分析
---

## 背景

一次请求需要从 kv 中查询大量信息，kv 中存储的是 pb 的 `message` 序列化后的数据，大量反序列化操作将 CPU 打满导致超时，通过火焰图分析问题在 pb 数据解析上

当 pb 的 `message` 比较复杂的时候，大量的反序列化及其析构会占用大量的 CPU，同时影响耗时

## 方案一

重新定义一个 `message`，在 `message` 中只定义需要使用的字段，并保持字段类型、序号不变

## 方案二

使用场景增多后，需要定义更多的新 `message` 导致维护困难

pb 的 `CodedInputStream` 可以自定义二进制字节的反序列化过程，并且可以实现跳过某些字段的功能

将需要解析的字段序号存储在 `set` 中，通过 pb 的反射拿到字段名后去 `set` 中判断是否需要解析

遇到需要解析的字段需要自己来完成解析过程，主要是根据数据类型来强转指针

## 方案三

方案二有一个缺点：直接使用了原始 pb 来解析，如果后续需要用到新的字段，但是忘记加到 `set` 中可能并不容易发现，很可能导致线上策略 bug

1. 定义一个模板类继承原始 `message`，这样能直接拥有字段名的访问函数

```cpp
Status LitePBMessageParse(const char* data, size_t size,
                                const std::unordered_set<uint32_t>& field_number_set, Message* msg);

template <typename T, const char*... Strings>
class LitePBMessageWrapper : public T {
 public:
    LitePBMessageWrapper() : filed_names_{Strings...} {}
    bool ParseFromString(const std::string& str) {
        auto status = LitePBMessageParse(str.data(), str.size(), filed_names_, this);
        return status.ok();
    }
    bool ParseFromArray(const char* data, size_t size) {
        auto status = LitePBMessageParse(data, size, filed_names_, this);
        return status.ok();
    }

    std::unordered_set<std::string> filed_names_;
};
```

2. 限制没有解析的字段不被访问，可以通过使用私有继承 +子类重新 using 的方式来实现这个按需放出父类函数的功能

## 对象池

如果用对象池做到大 PB 对象的复用，每次用完 `Clear`。但 `Clear` 的时候，一级的字段的内存有保留，但是二级三级的字段还是会被真的释放掉，除非自定义 `Clear` 方法或者潜逃对象池