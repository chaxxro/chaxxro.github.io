# 正则表达式

## 字符匹配

|字符|描述
|-|-|
`\`|转义符
`\w`|匹配所有字母数字和下划线，等同于 `[a-zA-Z0-9_]`
`\W`|匹配所有非字母数字，等同于 `[^\w]`
`\d`|匹配数字 `[0-9]`
`\D`|匹配非数字 `[^\d]`
`\s`|匹配任何空白字符，包括空格、制表符、换行符、换页符和回车符等等
`\S`|匹配任何非空白字符 `[^\s]`
`\f`|匹配一个换页符
`\n`|匹配一个换行符
`\r`|匹配一个回车符
`\t`|匹配一个水平制表符
`\v`|匹配一个垂直制表符
`\p`|匹配 `CR/LF`，用来匹配 DOS 行终止符
`\cx`|匹配由 x 指明的控制字符，例如 `\cM` 匹配一个 `Control-M` 或回车符，`x` 的值必须为 `A-Z` 或 `a-z` 之一，否则将 `c` 视为一个原义的 `c` 字符
`uxxxx`|查找以十六进制数 `xxxx` 规定的 Unicode 字符
`.`|匹配除换行符、回车符、行分隔符和段分隔符之外的任何单字符
`[]`|中括号表达式，匹配方括号内的任意字符
`[^]`|匹配除了方括号内的任意字符

## 位置匹配

|字符|描述
|-|-|
`\b`|匹配一个字边界，即字与空格间的位置
`\B`|非字边界匹配
`^`|行开头
`$`|行尾

## 量词

|字符|描述
|-|-|
`*`|前面的表达式匹配零次或多次
`+`|前面的表达式匹配一次或多次
`?`|前面的表达式匹配零次或一次
`{n}`|前面的表达式确定匹配 n 次
`{n,}`|前面的表达式至少匹配 n 次
`{n,m}`|前面的表达式最少 n 次最多 m 次

## 组

|字符|描述
|-|-|
`(abc)`|捕获组，匹配与 xyz 完全相等的字符串
`\n`|引用第 n 个捕获组，n 是正整数
`(?:abc)`|非捕获组

## 先行断言

|字符|描述
|-|-|
`a(?=b)`|a 只有在 b 前面才匹配
`a(?!b)`|a 只有不在 b 前面才匹配

## 后行断言

|字符|描述
|-|-|
`(?<=b)a`|a 只有在 b 后面才匹配
`(?<!b)a`|a 只有不在 b 后面才匹配

## 分支

|字符|描述
|-|-|
`\|`|或运算，匹配符号前或后的字符

## 修饰符

|字符|描述
|-|-|
`/i`|大小写不敏感
`/g`|全局匹配，查找所有匹配项
`/m`|多行匹配

## 特殊表达式

- `$&`：正则表达式匹配的文本

- ```$` ```：匹配文本的左侧内容

- `$'`：匹配文本的右侧内容