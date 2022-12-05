# grep

全面搜索正则表达式并把行打印出来

用基本的 Unix 风格正则表达式来匹配模式

```sh
grep [options] pattern [file]

# 不要忽略二进制数据
-a --text
# 除了显示符合范本样式的那一行之外，并显示该行之后的内容
-A <显示行数>   --after-context=<显示行数>
# 在显示符合范本样式的那一行之外，并显示该行之前的内容
-b --byte-offset
# 除了显示符合样式的那一行之外，并显示该行之前的内容
-B<显示行数>   --before-context=<显示行数>
# 计算符合范本样式的行数
-c --count
# 除了显示符合范本样式的那一列之外，并显示该列之前后的内容
-C<显示行数> --context=<显示行数>或-<显示行数>
# 当指定要查找的是目录而非文件时，必须使用这项参数，否则grep命令将回报信息并停止动作
-d<进行动作> --directories=<动作>
# 指定字符串作为查找文件内容的范本样式
-e<范本样式> --regexp=<范本样式>
# 将范本样式为延伸的普通表示法来使用，意味着使用能使用扩展正则表达式
-E --extended-regexp
# 指定范本文件，其内容有一个或多个范本样式，让grep查找符合范本条件的文件内容，格式为每一列的范本样式
-f<范本文件> --file=<规则文件>
# 将范本样式视为固定字符串的列表
-F --fixed-regexp 
# 将范本样式视为普通的表示法来使用
-G --basic-regexp
# 在显示符合范本样式的那一列之前，不标示该列所属的文件名称
-h --no-filename
# 在显示符合范本样式的那一列之前，标示该列的文件名称
-H --with-filename
# 忽略字符大小写的差别
-i --ignore-case
# 列出文件内容符合指定的范本样式的文件名称
-l --file-with-matches
 # 列出文件内容不符合指定的范本样式的文件名称
-L --files-without-match
# 在显示符合范本样式的那一列之前，标示出该列的编号
-n --line-number
# PATTERN 是一个 Perl 正则表达式
-P --perl-regexp
# 不显示任何信息
-q --quiet或--silent
# 此参数的效果和指定“-d recurse”参数相同
-R/-r  --recursive
# 不显示错误信息
-s --no-messages
# 反转查找，输出不包含匹配项的行
-v --revert-match
# 显示版本信息
-V --version
# 只显示全字符合的列
-w --word-regexp
# 只显示全列符合的列
-x --line-regexp
# 只输出文件中匹配到的部分
-o
# 找到num行结果后停止查找，用来限制匹配行数
-m <num> --max-count=<num>
```