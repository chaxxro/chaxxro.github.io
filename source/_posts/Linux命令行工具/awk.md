---
toc:
  enable: true
  number: false
  max_depth: 3
title: awk
date: 2023-04-25 20:17:47
tags: 命令行工具
categories: Linux 命令行
---

awk 把文件逐行的读入，以空格和制表符为默认分隔符将每行切片，切开的部分再进行各种分析处理

```sh
awk [options] '[BEGIN{ command }] pattern { action } ... [END{ command }]' file
# 1. 在读取文件之前执行 BEGIN 代码块，只执行一次，无法使用 $0 或其它一些特殊变量
# 2. 逐行扫描文件，每行执行 pattern { action }
#       - pattern 用于筛选行，action 表示在筛选通过后执行的操作
#       - 多个 pattern{action} 可以直接连接连用
#       - action 中多个语句如果写在同一行，则需使用分号分隔
#       - 省略 pattern，等价于对每一行数据都执行 action 
#       - 省略代码块 {action}，等价于 {print} 即输出所有行
#       - 省略代码块中的 action，表示对筛选的行什么都不做
#       - BEGIN 和 END 其实是特殊 pattern
# 3. 在读取文件完成之后执行 END 代码块，可以使用 $0 等一些特殊变量，只不过这些特殊变量保存的是最后一行数据

# pattern 布尔代码块
/regular expression/    # 正则匹配成功与否 /a.*ef/{action}
relational expression   # 即等值比较、大小比较 3>2{action}
pattern && pattern      # 逻辑与 3>2 && 3>1 {action}
pattern || pattern      # 逻辑或 3>2 || 3<1 {action}
! pattern               # 逻辑取反 !/a.*ef/{action}
(pattern)               # 改变优先级
pattern ? pattern : pattern  # 三目运算符决定的布尔值
# pattern 范围代码块
pattern1, pattern2      # 范围，pat1打开、pat2关闭，即flip,flop模式

# options:
-F 指定分隔符，默认使用空格分割
-v var=value 复制一个用户变量，将外部变量传递给 awk
-f 从脚本文件读取 awk 命令

awk 内置变量：
1. NR 表示文件中的行号，表示当前是第几行
2. NF 表示文件中的当前行被分割的列数
3. 根据分隔符将每一行分为若干字段，依次用 $1, $2,$3 来表示，$0 表示整行

awk 'BEGIN{n=3} /^[0-9]/{$1>5{$1=333;print $1} /Alice/{print "Alice"} END{print "hello"}' a.txt

awk -F ':' '{print $1}' /etc/passwd

awk '{$2 = "***"; print $0}' fruit.txt

awk '{print $1 "\t" $2 "\t" $3}' fruit.txt

awk '{print NR "\t" $0}' fruit.txt

awk '{print NF "\t" $0}' fruit.txt

awk '{num = 10; if (num % 2 == 0) printf "%d 是偶数\n", num }'

awk '{
    num = 11; 
    if (num % 2 == 0) printf "%d 是偶数\n", num; 
    else printf "%d 是奇数\n", num 
}'

awk '{ for (i = 1; i <= 5; ++i) print i }'

awk '{i = 1; while (i < 6) { print i; ++i } }'

awk '{
   sum = 0; for (i = 0; i < 20; ++i) { 
      sum += i; if (sum > 50) break; else print "Sum =", sum 
   } 
}'

awk '{for (i = 1; i <= 20; ++i) {if (i % 2 == 1) continue ; else print i} }'

引用 shell 中其他变量方式
1. 使用 "' '"  双引号+单引号+shell变量+单引号+双引号
shell_var="abc"
awk '{printf "'$shell_var'"}'

2. 使用 "'" "'"  双引号+单引号+双引号+shell变量+双引号+单引号+双引号
shell_var="this a test"
awk '{printf "'"$shell_var"'"}'

3. -v 
shell_var="this a test"
awk -v awk_var="$shell_var" '{print awk_var}'
```