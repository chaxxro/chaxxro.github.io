---
toc:
  enable: true
  number: false
  max_depth: 3
title: mail
date: 2023-04-26 19:42:37
tags: 网络协议
categories: 网络协议
---

- SMTP 只能发送 ASCII 码，而互联网邮件扩充 MIME 可以发送二进制文件。MIME 并没有改动或者取代 SMTP，而是增加邮件主体的结构，定义了非 ASCII 码的编码规则

{% asset_img 01.png %}

- POP3 只要用户从服务器上读取了邮件，就把该邮件删除

- IMAP 中客户端和服务器上的邮件保持同步，如果不手动删除邮件，那么服务器上的邮件也不会被删除