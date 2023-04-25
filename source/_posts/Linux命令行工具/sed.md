---
toc:
  enable: true
  number: false
  max_depth: 3
title: sed
date: 2023-04-25 21:19:13
tags: 命令行工具
categories: Linux 命令行
---

`sed` 把当前处理的行存储在临时缓冲区中，接着用 `sed` 脚本处理缓冲区中的内容，处理完成后，把缓冲区的内容送往屏幕，接着处理下一行，直到文件末尾

```sh
sed [option]... [-e '<script>']... [-f '<script 文件>'] [文本文件]
# 选项
# -i 直接修改原文件
# -n 关闭默认输出，即不在屏幕上自动打印
# -r 使用正则
# -e 指定脚本，可指定多个脚本
# -f 指定脚本文件

sed '[address]op[/pattern][/replacement][/flags]' fileName

# address
# 不给地址时表示对全文进行处理
# n 在第 n 行执行脚本，$ 表示最后一行
# n,m 在 n~m 行执行脚本
# n,+m 在 n~n+m 行执行脚本
# /RE/ 匹配正则 /RE/ 的行
# n,/RE/  n~匹配 /RE/ 的行执行脚本
# /RE/,m  匹配 /RE/ 的行~m 执行脚本
# /RE1/,/RE2/  匹配 /RE1/ 的行 ~ 匹配 /RE2/ 执行脚本

# op
# p：打印行
# d：行删除
# a：在当前行下面追加新的行，使用 \n 追加多行
# i：在当前行上面插入新的行
# c：行替换
# s：字符替换
# w：把行写入文件
# q：退出

# flags
# g：行内全面替换
# num：只替换行内第 num 个匹配项
# numg：从第 num 处匹配全部
# \1：子串匹配标记
# &：已匹配字符串标记

# 字符替换脚本
sed 's/test/trial/2' data4.txt
sed 's/test/trial/w test.txt' data5.txt
sed 's/\/bin\/bash/\/bin\/csh/' /etc/passwd

# 替换行脚本
sed '[address]c\用于替换的新文本' fileName
sed '3c\This is a changed line of text.' data6.txt

# 删除脚本
sed '[address]d' fileName
# 删除文本中的特定行
sed '3d' data6.txt
sed '2,3d' data6.txt
# 删除某个区间内的行
# 第一个模式会打开行删除功能，第二个模式会关闭行删除功能
sed '/1/,/3/d' data6.txt
sed '3,$d' data6.txt

# 插入脚本
sed '[address]a（或 i）\新文本内容' fileName
sed '3a\This is an appended line.' data6.txt
# 将一个多行数据添加到数据流中，只需对要插入或附加的文本中的每一行末尾（除最后一行）添加反斜线即可

# 转换脚本
sed '[address]y/inchars/outchars/' fileName
# 对 inchars 和 outchars 值进行一对一的映射
# inchars 中的第一个字符会被转换为 outchars 中的第一个字符
# 第二个字符会被转换成 outchars 中的第二个字符...
# 转换命令是一个全局命令
sed 'y/123/789/' data8.txt

# 打印脚本
sed '[address]p' fileName

# 另存脚本
sed '[addrress]w' fileName
# 可以使用相对路径或绝对路径
sed '1,2w test.txt' data6.txt

# 插入文件脚本
sed '[address]r filename' fileName
# 将一个独立文件的数据插入到当前数据流的指定位置
sed '3r data12.txt' data6.txt
sed '$r data12.txt' data6.txt

# 行号
# 在脚本命令中，指定的地址可以是单个行号
# 或是用起始行号、逗号以及结尾行号指定的一定区间范围内的行
```
