---
toc:
  enable: true
  number: false
  max_depth: 3
title: rpc
date: 2023-06-08 10:19:27
tags: 常见概念
categories: 常见概念
---

从 rpc 的调用关系看，分为客户端和服务端

## 路由标识

一个服务的地址可以看作是 IP + Port + 协议

从服务寻址角度看，服务需要一个路由标识来获取服务的地址

路由标识必须全局唯一，且一般通过名字服务进行管理，所以路由标识也叫服务名或 Naming Service

客户端通过路由标识向名字服务获取服务地址

## 接口标识

rpc 调用接口也需要一个全剧唯一标识，称为接口标识或 RPC Name

利用 pb 自动生成接口时，接口标识格式可使用 `/package.proto_service/method`

- package 对应 pb 中的 package，可以理解为一个支持多级的名字空间，用来防止接口命名冲突

- proto_service 对应 pb 中的 service，是一组 rpc 方法的集合，它是对接口的一个逻辑分组

- method 对应 pb 中的 rpc 方法，每个 method 必须且只能属于一个 proto_service，一个proto_service 允许定义多个 method

## 接口映射

proto_service 负责定义 rpc 接口的定义和归类，Naming Service 负责网络连接和协议处理

需要把 proto_service 和 Naming Service 关联起来，通过把 proto_service 注册到 Naming Service 来完成服务的组装