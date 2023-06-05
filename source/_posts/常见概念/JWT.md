---
toc:
  enable: true
  number: false
  max_depth: 3
title: JWT
date: 2023-06-05 14:53:21
tags: 常见概念
categories: 常见概念
---

JWT 即 Json Web Token，是一种跨域认证解决方案

## 跨域认证

用户认证一般流程

1. 用户向服务器发送用户名和密码

2. 服务器验证通过后，在当前 session 里面保存相关数据，比如用户角色、登录时间等等

3. 服务器向用户返回一个 session_id，写入用户的 Cookie

4. 用户随后的每一次请求，都会通过 Cookie 将 session_id 传回服务器

5. 服务器收到 session_id，找到前期保存的数据，由此得知用户的身份

该方案存在扩展性不好的问题，当遇到服务器集群或者是跨域的服务架构，就需要做到 session 数据共享才能使每台服务器都能读到 session

为了解决 session 共享问题，有两种方案

1. 将 session 持久化，这样服务收到请求向持久层请求数据

2. 服务端不保存 session，将 session 保存在客户端，这样客户端每次请求到将 session 发回服务端

JWT 就是改良方案二的一个代表

## JWT 原理

JWT 是一个很长的字符串，由 Header 头部、Payload 负载和 Signature 签名组成，中间用点 . 分隔成三个部分

```
Header.Payload.Signature
```

### Header

Header 是一个 JSON 对象，描述 JWT 的元数据，包括以下字段

- alg：签名算法，默认 HS256

- typ：token 类型，JWT 统一为 JWT

最后需要将 Header 的 JSON 对象使用 Base64URL 算法转成字符串

### Payload

Payload 是一个 JSON 对象，描述需要传递的信息，包括以下字段

- iss：issuer 签发人

- exp：expiration time 过期时间

- sub：subject 主题

- aud：audience 受众

- nbf：not before 生效时间

- iat：issued at 签发时间

- jti：JWT id 编号

除了官方字段，还可以在这个部分定义私有字段

最后需要将 Payload 的 JSON 对象使用 Base64URL 算法转成字符串

### Signature

Signature 是对前两部分利用私钥的签名，防止数据篡改

服务端根据 Header 中的算法，利用私钥、 Header 和 Payload 计算签名，再使用 Base64URL 转成字符串

## 使用方法

- 客户端每次与服务器通信都要带上这个 JWT，可以把它放在 Cookie 里面自动发送，但是这样不能跨域

- 将 JWT 放在 HTTP 请求的头信息 Authorization 字段里面，这样就解决了跨域的问题

- JWT 放在 POST 请求的数据体里面，这样也能解决了跨域的问题

## 特点

- JWT 默认是不加密，但也可以生成原始 Token 以后用密钥再加密一次

- JWT 不加密的情况下，不能将秘密数据写入 JWT

- JWT 不仅可以用于认证，也可以用于交换信息

- 由于服务器不保存 session 状态，因此无法在使用过程中废止某个 token，或者更改 token 的权限，除非服务器部署额外的逻辑

- JWT 本身包含了认证信息，一旦泄露任何人都可以获得该令牌的所有权限，所以 JWT 的有效期应该设置得比较短

- 为了减少盗用，JWT 不应该使用 HTTP 协议明码传输，要使用 HTTPS 协议传输