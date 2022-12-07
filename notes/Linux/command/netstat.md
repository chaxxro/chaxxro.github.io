# netstat

查看网络连接状态

```sh
netstat [-acCeFghilMnNoprstuvVwx][-A<网络类型>][--ip]

-a 列出所有端口使用情况，netstat 默认不显示 LISTEN 相关选项
-t (tcp) 仅显示tcp相关选项
-u (udp)仅显示udp相关选项
-n 不显示别名，能显示数字的全部转化为数字
-l 仅列出在 Listen 的服务状态
-p 显示建立相关链接的程序名
-e 显示扩展信息
-c 每隔一个固定时间执行命令
-s 显示网络统计信息

# 列出所有信息
netstat -a
# 不是使用域名
netstat -an
# 只显示监听端口
netstat -l
# 显示PID和进程名称
netstat -anp
```