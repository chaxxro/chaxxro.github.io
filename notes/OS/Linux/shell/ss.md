# ss

`ss` 命令用来替代 `netstat` 的

```sh
-a 显示服务器上所有的 sockets 连接，直接列出所有网络连接
-l 显示正在监听的网络端口
-n 显示数字IP和端口，不通过域名服务器
-p 显示使用 socket 的对应的程序
-t 只显示 TCP sockets
-u 只显 示UDP sockets
-4 -6 只显示 v4 或 v6 版本的 sockets
-s 查看当前服务器的网络连接统计，打印出统计信息。
-0 显示 PACKET sockets
-w 只显示 RAW sockets
-x 只显示 UNIX 域 sockets
-r 尝试进行域名解析，地址/端口
```