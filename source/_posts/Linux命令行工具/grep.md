---
toc:
  enable: true
  number: false
  max_depth: 3
title: grep
date: 2023-03-17 21:11:47
tags: 命令行工具
categories: Linux 命令行
---

```sh
grep [-abcdDEFGHhIiJLlMmnOopqRSsUVvwXxZz] [-A num] [-B num] [-C[num]]
     [-e pattern] [-f file] [--binary-files=value] [--color[=when]]
     [--colour[=when]] [--context[=num]] [--label] [--line-buffered]
     [--null] [pattern] [file ...]
```

`-a`、`--text` 不要忽略二进制数据

`-A num`、`--after-context=num` 除了显示符合表达式的行之外，还显示该行之后 num 行的内容

`-b`、`--byte-offset` 除了显示符合表达式的行之外，还显示该行之前的内容

`-B num`、`--before-context=num` 除了显示符合表达式的那一行之外，并显示该行之前 num 行的内容

`-c`、`--count` 只显示指定数量的行

`-Cnum`、`--context=num` 除了显示符合表达式的那一行之外，并显示该行前后的内容，默认值是 2，等于 `-A 2 -B 2`

`-d action`、`--directories=action` 当要查找的是目录时默认 read 将目录当作普通文件，skip 表示跳过目录，recurse 表示递归目录，等同于 `-R` 和 `-r`

`-D action`、`--devices=action` 当要查找的是设备、fifo、socket 时默认 read 将目录当作普通文件，skip 跳过该文件

`-e pattern`、`--regexp=pattern` 指定字符串作为查找文件内容的表达式

`-E`、`--extended-regexp` 表达式使用扩展正则 ere 表达式，等价于 `egrep`

`--exclude pattern` 排除带绝对路径文件名匹配 pattern 的文件

`--exclude-dir pattern` 如果指定了 `-R`，排除目录

-f file, --file=file

-F --fixed-regexp，等价于 `fgrep`，只做精准匹配

`-G`、`--basic-regexp` 将表达式视为普通的表示法来使用

`-h`、`--no-filename` 在显示符合表达式的那一行之前，不标示该列所属的文件名称

`-H` 在显示符合表达式的那一行之前，标示该列的文件名称

`-i`、`--ignore-case` 忽略大小写

`-I` 忽略二进制文件，等同于 `--binary-file=without-match`

`--include pattern` 只搜索带绝对路径文件名匹配 pattern 的文件

`--include-dir pattern` 如果指定了 `-R`，只搜索匹配上的目录

`-l`、`--file-with-matches` 列出文件内容符合指定的表达式的文件名称

`-L`、`--files-without-match` 列出文件内容不符合指定的表达式的文件名称

`-m num`、`--max-count=num` 指定最大匹配数

`-n`、`--line-number` 在显示符合范本样式的那一行之前，标示出该列的编号

`-o` 只输出文件中匹配到的部分

`-O` 跟随软链

`-p` 不跟随软链

`-q`、`--quiet`、`--silent` 不显示任何信息

`-R`、`-r`、`--recursive` 和指定 -d recurse 参数相同

`-s`、`--no-messages` 不显示错误信息

`-v`、`--revert-match` 反转查找，输出不包含匹配项的行

`-w`、`--word-regexp` 只显示全字符合的列

`-x`、`--line-regexp` 只显示全列符合的列

```sh
# 查询以 .Pp 开头的行
grep '^\.Pp' myfile
# 查找不包含 foo 或 bar 的行
grep -v -e 'foo' -e 'bar' myfile
# 递归查找指定目录下所有 .h 文件
grep -H -R FIXME --include="*.h" /usr/src/sys/arm/
```
