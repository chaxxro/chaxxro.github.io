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

`sed` 的工作流程：

1. 读取输入流的一行到模式空间，输入流可以是标准输入也可以是文件

2. 通过行号计数器记录当前行号

3. 对模式空间中的内容进行匹配和处理

4. 自动输出模式空间内容

5. 清空模式空间内容

6. 读取输入流的下一行到模式空间

```sh
sed [option]... [-e '<script>']... [-f '<script 文件>'] [文本文件]
# 选项
# -i['suffix'] sed 通过创建一个临时文件并将输出写入到临时文件，然后重命名为源文件来实现的对源文件的覆盖的，指定 suffix 后会将源文件备份
# -n 关闭默认输出，即不在屏幕上自动打印
# -r 使用扩展正则
# -e 指定脚本，可指定多个脚本
# -f 指定脚本文件

sed '[address]op[/pattern][/replacement][/flags]' fileName

# address
# 不给地址时表示对全文进行处理
# n 在第 n 行执行脚本，$ 表示最后一行
# n,m 在 n~m 行执行脚本
# n,+m 在 n~n+m 行执行脚本
# n~m 取行号满足 n+(x*m) 的行
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
# s：正则字符替换，对应 flags 有 g 全部替换，p 输出替换后的内容，i 不区分大小写
# w：把行写入文件
# q：退出
# =: 输出行号
# n: 读取下一行

# flags
# g：行内全面替换
# num：只替换行内第 num 个匹配项
# numg：从第 num 处匹配全部
# \1：子串匹配标记
# &：已匹配字符串标记

# 字符替换脚本
sed 's/test/trial/2' data4.txt
sed 's/test/trial/w test.txt' data5.txt

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
```
