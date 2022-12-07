# find

`find` 命令中的表达式有四种类型

- Tests 就是我们最常用的指定查找文件的条件

- Actions 对找到的文件可以做的操作

- Global options 全局属性用来限制一些查找的条件，比如常见的目录层次深度的限制

- Positional options 位置属性用来指定一些查找的位置条件

## TESTS

`find` 命令是通过文件属性查找文件的，比如文件的各种时间，文件权限等

很多参数中会出现指定一个数字 n，一般会出现三种写法

- `+n` 表示大于 [n + 1, ...)
 
- `-n` 表示[0, n)
 
- `n` 表示[n, n + 1)

### 根据时间查找

`-mtime` 以天为单位通过 modify time 查找文件

`-ctime` 以天为单位通过 change time 查找文件

`-atime` 以天为单位通过 access time 查找文件

`-mmin` 以分钟为单位通过 modify time 查找文件

`-cmin` 以分钟单位通过 change time 查找文件

`-amin` 以分钟为单位通过 access time 查找文件

`-anewer file` 比较文件的 access time

`-cnewer file` 比较文件的 change time

`-newer file` 比较文件的 modify time

`-newerXY file` 其中 Y 表示的是跟后面 file 的什么时间比较，而 X 表示使用查找文件什么时间进行比较

### 根据用户查找

`-uid n` 文件的所属用户 uid 为 n

`-user name` 文件的所属用户为 name

`-gid n` 文件的所属组 gid 为 n

`-group name` 所属组为 name 的文件

`-nogroup` 没有所属组的文件

`-nouser` 没有所属用户的文件

### 根据权限查找

`-executable` 文件可执行

`-readable` 文件可读

`-writable` 文件可写

`-perm mode` 查找权限为 mode 的文件，mode 的写法可以是数字，也可以是 `ugo=rwx`

```sh
find /etc/ -perm 644 -ls
# 等同于
find /etc/ -perm u=rw,g=r,o=r -ls
```

mode 指定的是完全符合这个权限的文件，没描述的权限就相当于指定了没有这个权限

mode 还可以使用 `/` 或 `-` 作为前缀进行描述，表示没指定的权限是忽略的

### 根据路径查找

`-name pattern` 文件名为pattern指定字符串的文件。注意如果pattern中包括*等特殊符号的时候，需要加”“。

`-iname` 忽略大小写

`-lname pattern` 查找符号连接文件名为 pattern 的文件

`-ilname` 忽略大小写的符号连接

`-path pattern` 根据完整路径查找文件名为 pattern 的文件

`-ipath` path 忽略大小写

`-regex pattern` 用正则表达式匹配文件名

`-iregex` regex 忽略大小写

### 其他状态查找

`-empty` 文件为空而且是一个普通文件或者目录

`-size n[cwbkMG]` 指定文件长度查找文件，c 字节为单位；b 块为单位，块大小为 512 字节，这个是默认单位；w 表示两个字节；k 以1024字节为单位；M 以 1048576 字节为单位；G 以 1073741824 字节为单位

`-type c` 以文件类型查找文件，c 可以选择的类型为：b 块设备；c 字符设备；d 目录；p 命名管道；f 普通文件；l 符号连接；s socket

## ACTIONS

actions 类型参数主要是用来对找到的文件进行操作的参数

`-ls 参数对找到的文件进行长格式显示

`-fls file` 将信息写入指定的文件，而不是显示在屏幕上

`-print` 将找到的文件显示在屏幕上，实际上默认 `find` 命令就会将文件打印出来显示

`-delete` 可以将找到的文件直接删除