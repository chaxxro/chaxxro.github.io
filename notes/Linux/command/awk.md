# awk

awk 把文件逐行的读入，以空格和制表符为默认分隔符将每行切片，切开的部分再进行各种分析处理

```
awk [options] 'script' file

options:
-F 指定分隔符
-v var=value 复制一个用户变量，将外部变量传递给 awk
-f 从脚本文件读取 awk 命令

awk 根据分隔符将每一行分为若干字段，依次用 $1, $2,$3 来表示，$0 表示整行
awk 内置变量：
1. NR 表示文件中的行号，表示当前是第几行、
2. NF 表示文件中的当前行被分割的列数

script 由模式和操作组成
模式包括：
1. /正则表达式/：使用正则
2. 关系表达式：使用运算符进行操作，可以是字符串或数字的比较
3. 模式匹配表达式：运算符 ～(匹配) 和 !~(不匹配)
4. BEGIN 语句块、pattern 语句块、END 语句块
操作由一个或多个命令、函数、表达式组成，之间用换行符或分号隔开，被 {} 花括号包围

awk 'BEGIN{ print "start" } pattern{ commands } END{ print "end" }' file
1. 执行 BEGIN{ commands } 语句块中的语句；
2. 从文件或标准输入(stdin)读取一行，然后执行 pattern{ commands } 语句块，它逐行扫描文件，从第一行到最后一行重复这个过程，直到文件全部被读取完毕。
3. 当读至输入流末尾时，执行 END{ commands } 语句块

awk -F ':' '{print $1}' /etc/passwd

awk '{$2 = "***"; print $0}' fruit.txt

awk '{print $1 "\t" $2 "\t" $3}' fruit.txt

awk '{print NR "\t" $0}' fruit.txt

awk '{print NF "\t" $0}' fruit.txt

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
awk '
{printf "'$shell_var'"}'

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


