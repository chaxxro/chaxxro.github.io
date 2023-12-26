---
toc:
  enable: true
  number: false
  max_depth: 3
title: post
date: 2023-12-26 16:43:02
tags: 操作系统
categories: Linux环境变量
---

## PWD

当前地址

## LD_PRELOAD

动态链接库在加载过程中，动态链接器会先读取 `LD_PRELOAD` 环境变量和默认配置文件 /etc/ld.so.preload，即使程序不依赖这些动态链接库，`LD_PRELOAD` 环境变量和 /etc/ld.so.preload 配置文件中指定的动态链接库依然会被加载，因为它们的优先级比 `LD_LIBRARY_PATH` 环境变量所定义的链接库查找路径的文件优先级要高，所以能够提前于用户调用的动态库载入

LD_PRELOAD > LD_LIBRARY_PATH > /etc/ld.so.cache > /lib > /usr/lib

```sh
export LD_PRELOAD=$PWD/xx.so
# 可以从 ldd 中查看是否生效

export -n LD_PRELOAD=$PWD/xx.so # 删除
```