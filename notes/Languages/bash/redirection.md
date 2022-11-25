# 重定向

```sh
# 将输出重定向到 file
command > file   
# 将输入重定向到 file
command < file  
# 将输出以追加的方式重定向到 file
command >> file

# 0 通常是标准输入 STDIN
# 1 是标准输出 STDOUT
# 2 是标准错误输出 STDERR

# 复制文件描述符
# 复制输入文件描述符
[n]<&word
# n 默认是 0
# word 是一个已经打开并且用作输入的文件描述符
# word 写的是 - 符号，表示关闭这个文件描述符

# 复制输出文件描述符
# n 默认是 1
[n]>&word

# 只看报错信息
find /etc -name passwd > /dev/null
# 只看正确输出信息
find /etc -name passwd 2> /dev/null
# 将标准报错输出重定向到标准输出
find /etc -name passwd 2>&1
# 什么信息都不看
find /etc -name passwd > /dev/null 2 >&1

# 移动文件描述符
# 移动输入描述符
[n]<&digit-
# 移动输出描述符
[n]>&digit-
# 将原有描述符在新的描述符编号上打开，并且关闭原有描述符

# 新建文件描述符
# 新建一个用来输入的描述符
[n]<word
# 新建一个用来输出的描述符
[n]>word
# 新建一个用来输入和输出的描述符
[n]<>word
# word都应该写一个文件路径，用来表示这个文件描述符的关联文件是谁
```

一般输入输出重定向都是放到命令后面作为后缀使用，所以如果单纯改变脚本的描述符，需要在前面加 `exec` 命令

```sh
# 打开 3 号 fd 用来输入，关联文件为 /etc/passwd
exec 3< /etc/passwd
# 让 3 号描述符成为标准输入
exec 0<&3
# 关闭 3 号描述符
exec 3>&-
# 打开 3 号和 4 号描述符作为输出，并且分别关联文件
exec 3> /tmp/stdout
exec 4> /tmp/stderr
# 将标准输入关联到 3 号描述符，关闭原来的 1 号 fd
exec 1>&3-
# 将标准报错关联到 4 号描述符，关闭原来的 2 号 fd
exec 2>&4-
```