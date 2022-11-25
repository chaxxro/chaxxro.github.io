# bash 脚本

bash 编程贯彻了 C 程序的设计哲学，一切皆表达式

bash 在执行任何东西的时候都会有一个返回值，因为根据表达式的定义，任何表达式都必须有一个值，返回值也限定了取值范围 0-255

跟 C 语言含义相反，bash 中 0 为 true，非 0 为 false

## 指定 shell

在创建 shell 脚本文件时，必须在文件的第一行指定要使用的 shell

```sh
#!/bin/bash options
# 声明本脚本交给那个解释器进行解释

# options 是一些可以改变 shell 行为的选项，等同于 set
-f 禁止文件名展开（globbing）
-i 让脚本以 交互模式运行
-n 读取命令，但不执行（语法检查）
-t 执行完第一条命令后退出
-v 在执行每条命令前，向 stderr 输出该命令
-x 在执行每条命令前，向 stderr 输出该命令以及该命令的扩展参数
```

## 注释

`#` 用作注释行

多行注释，用 `:<<EOF` 开头，`EOF` 结尾

## 字符串输出

```sh
echo This is a test
```

在 `echo` 命令后面加上了一个字符串，该命令就能显示出这个文本字符串

默认情况下，不需要使用引号将要显示的文本字符串划定出来，但有时在字符串中出现引号的话就比较麻烦了

`echo` 命令可用单引号或双引号来划定文本字符串，如果在字符串中用到了它们，则需要在文本中使用其中一种引号，而用另外一种来将字符串划定起来

```sh
$ echo "This is a test to see if you're paying attention"
This is a test to see if you're paying attention

$ echo 'Rich says "scripting is easy".'
Rich says "scripting is easy".
```

## 格式化输出

```sh
printf "%d %s" 1 "hello"
```