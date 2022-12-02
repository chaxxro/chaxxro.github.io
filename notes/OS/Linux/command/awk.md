# awk

awk 把文件逐行的读入，以空格和制表符为默认分隔符将每行切片，切开的部分再进行各种分析处理

```
awk [options] 'script' file

options 这个表示一些可选的参数选项

script 表示可执行脚本代码（一般被 {} 花括号包围），这个是必须的

file 表示需要处理的文件，必须是纯文本文件

awk 根据分隔符将每一行分为若干字段，依次用 $1, $2,$3 来表示，$0 表示整行

awk 内置变量：

1. NR 表示文件中的行号，表示当前是第几行、

2. NF 表示文件中的当前行被分割的列数


awk -F ':' '{print $1}' /etc/passwd：使用 -F 来改变分隔符为 :，用 print 将第 1 列字段的内容打印输出

awk '{$2 = "***"; print $0}' fruit.txt：对 $2 变量进行重新赋值，来隐藏每一行的第 2 列内容，并且用星号 * 来代替其输出

awk '{print $1 "\t" $2 "\t" $3}' fruit.txt：在参数列表中加入一些字符串或者转义字符之类的，让输出的内容格式更漂亮，但一定要记住要使用双引号

awk '{print NR "\t" $0}' fruit.txt：内置 NR 变量表示每一行的行号

awk '{print NF "\t" $0}' fruit.txt：内置 NF 变量表示每一行的列数

搭配 if
awk '{num = 10; if (num % 2 == 0) printf "%d 是偶数\n", num }'

搭配 if-else
awk '{
    num = 11; 
    if (num % 2 == 0) printf "%d 是偶数\n", num; 
    else printf "%d 是奇数\n", num 
}'

搭配 for
awk '{ for (i = 1; i <= 5; ++i) print i }'

搭配 while
awk '{i = 1; while (i < 6) { print i; ++i } }'

搭配 break
awk '{
   sum = 0; for (i = 0; i < 20; ++i) { 
      sum += i; if (sum > 50) break; else print "Sum =", sum 
   } 
}'

搭配 continue
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

4. export 与 ENVIRON
shell_var="this a test";
export shell_var;
awk 'BEGIN{print ENVIRON["shell_var"]}' 
```


