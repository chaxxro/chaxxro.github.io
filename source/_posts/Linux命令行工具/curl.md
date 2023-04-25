---
toc:
  enable: true
  number: false
  max_depth: 3
title: curl
date: 2023-04-25 21:16:40
tags: 命令行工具
categories: Linux 命令行
---

模拟发送 HTTP 请求，默认行为是将目标页面输出到标准输出

```sh
curl url

# 页面保存到本地
curl url > index.html
curl -o index.html url

# 默认使用 GET 方法
# -X 指定具体方法
curl -X GET url
# curl 提供了另外的 -G 或 --get 进行设置使用 GET
# curl 使用 POST 时还需要 -d 指定 POST 数据
curl -X POST -d 'data' url

# -H 设置头部信息，多个头部信息需要多次 -H 设置
```