# if

```sh
if list; then list; elif list; then list; ... else list; fi
# bash 在解析字符的时候，; 跟回车是一样的，所以也可以下面这样
if list
then
	list
elif list
then
	list
...
else
	list
fi
# list 是若干个使用管道 ; & && 符号串联起来的 bash 命令序列
# 结尾可以以 , & && 或换行结束
```

`if` 后面判断什么都可以，因为 bash 无非就是把 `if` 后面的无论什么当成命令去执行，并判断其起返回值是真还是假

```sh
#!/bin/bash

DIR="/etc"

＃第一种写法
ls -l $DIR &> /dev/null
ret=$?

if [ $ret -eq 0 ]
then
		echo "$DIR is exist!" 
else
    	echo "$DIR is not exist!"
fi

#第二种写法
if ls -l $DIR &> /dev/null
then
        echo "$DIR is exist!" 
else
        echo "$DIR is not exist!"
fi
```

`[]` 是一个内建命令，等同于 `test` 命令

左中括号是调用 `test` 的命令标识，右中括号是关闭条件判断的，这个命令把它的参数作为比较表达式或者作为文件测试，并且根据比较的结果来返回一个退出状态码

```sh
if [ $ret -eq 0 ]
# 等同于
if test $ret -eq 0
```

## 条件判断

`test` 和 `[]` 中可用的比较运算符只有 `==` 和 `!=`，两者都是用于字符串比较的，不可用于整数比较，整数比较只能使用 `-eq`、`-gt` 这种形式

### 数字

关系运算符只支持数字，不支持字符串，除非字符串的值是数字

```sh
# -eq 检测两个数是否相等
# -ne 检测两个数是否不相等
# -gt 检测左边的数是否大于右边的
# -lt 检测左边的数是否小于右边的
# -ge 检测左边的数是否大于等于右边的
# -le 检测左边的数是否小于等于右边的
[ $a -eq $b ]
[ $a -ne $b ]
[ $a -gt $b ] 
[ $a -lt $b ] 
[ $a -ge $b ]
[ $a -le $b ]
```

### 逻辑

```sh
# ! 非运算
# -o 或运算
# -a 与运算
# && 逻辑的 AND
# || 逻辑的 OR
! [ $a -eq 10 ]
[ $a -lt 20 ] -o [ $b -gt 100 ]
[ $a -lt 20 ] -a [ $b -gt 100 ] 
[ $a -lt 100 ] && [ $b -gt 100 ] 
[ $a -lt 100 ] || [ $b -gt 100 ]
```

### 文件

```sh
# -e 判断对象是否存在
# -d 判断目录是否存在
# -f 判断常规文件是否存在
# -L 判断符号链接是否存在
# -h 判断软链接是否存在
# -s 判断对象是否存在，并且长度不为 0
# -r 判断可读文件是否存在
# -w 判断可写文件是否存在
# -x 判断有可执行权限文件是否存在
# -nt 判断 file1 是否比 file2 新
[ "/data/file1" -nt "/data/file2" ]
# -ot 判断 file1 是否比 file2 旧
[ "/data/file1" -ot "/data/file2" ]
```

### 字符串

```sh
# == 检测两个字符串是否相等
# != 检测两个字符串是否不相等
# -z 检测字符串长度是否为0
# -n 检测字符串长度是否不为 0
# $ 检测字符串是否为空
```