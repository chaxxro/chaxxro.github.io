# 基础语法

## 注释

```lua
-- 单行注释

--[[
 多行注释
 多行注释
 --]]
```

## 标识符

不要使用下划线加大写字母的标示符

不允许使用特殊字符如 `@`、`$`、`%` 来定义标示符

## 全局变量

在默认情况下，变量总是认为是全局的

全局变量不需要声明，给一个变量赋值后即创建了这个全局变量，访问一个没有初始化的全局变量也不会出错，只不过得到的结果是 `nil`

删除一个全局变量，只需要将变量赋值为 `nil`

## 数据类型

Lua 是动态类型语言，变量不要类型定义,只需要为变量赋值

Lua 中有 8 个基本类型分别为：`nil`、`boolean`、`number`、`string`、`userdata`、`function`、`thread` 和 `table`

|数据类型|描述|
|-|-|
nil|只有值 `nil` 属于该类，表示一个无效值，在条件表达式中相当于 `false`
boolean|`false` 和 `true`
number|双精度类型的实浮点数
string|由一对双引号或单引号来表示
function|由 C 或 Lua 编写的函数
userdata|任意存储在变量中的C数据结构
thread|线程
table|关联数组

可以使用 `type` 函数测试给定变量或者值的类型的字符串

```lua
print(type("Hello world"))      --> string
print(type(10.4*3))             --> number
print(type(print))              --> function
print(type(type))               --> function
print(type(true))               --> boolean
print(type(nil))                --> nil
print(type(type(X)))            --> string
```

### nil

对于全局变量和 `table`，`nil` 还有一个删除作用，给全局变量或者 `table` 表里的变量赋一个 `nil` 值，等同于把它们删掉

`nil` 作比较时应该加上双引号 `""`

```lua
type(X)==nil      -- false
type(X)=="nil"    -- true
```

### boolean

`boolean` 类型只有 `true` 和 `false`，Lua 把 `false` 和 `nil` 看作是 false，其他的都为 true，数字 `0` 也是 true

### number

Lua 默认只有一种 `number` 类型为 `double`，可以修改 luaconf.h 里的定义

### string

字符串由一对 `""` 或 `''` 来表示，也可以用 2 个方括号 `[[]]` 来表示一块字符串

```lua
html = [[
<html>
<head></head>
<body>
    <a href="http://www.xcharox.top/">page</a>
</body>
</html>
]]
```

在对一个数字字符串上进行算术操作时，Lua 会尝试将这个数字字符串转成一个数字

字符串连接使用的是 `..`

```lua
print("a" .. 'b')  -- ab
print(123 .. 456)  -- 123456
```

将 `#` 放在字符串前面来计算字符串的长度

```lua
print(#"hello")    -- 5
```

- `string.upper(argument)` 字符串全部转为大写字母

- `string.lower(argument)` 字符串全部转为小写字母

- `string.reverse(arg)` 字符串反转

- `string.format(...)` 返回一个类似 `printf` 的格式化字符串

```lua
--[[
%c - 接受一个数字, 并将其转化为ASCII码表中对应的字符
%d, %i - 接受一个数字并将其转化为有符号的整数格式
%o - 接受一个数字并将其转化为八进制数格式
%u - 接受一个数字并将其转化为无符号整数格式
%x - 接受一个数字并将其转化为十六进制数格式, 使用小写字母
%X - 接受一个数字并将其转化为十六进制数格式, 使用大写字母
%e - 接受一个数字并将其转化为科学记数法格式, 使用小写字母e
%E - 接受一个数字并将其转化为科学记数法格式, 使用大写字母E
%f - 接受一个数字并将其转化为浮点数格式
%q - 接受一个字符串并将其转化为可安全被Lua编译器读入的格式
%s - 接受一个字符串并按照给定的参数格式化该字符串
]]--
```

- `string.char(...)` 将整型数字转成字符并连接

- `string.byte(arg[,int])` 转换字符为整数值，默认第一个字符

- `string.len(arg)` 计算字符串长度

- `string.rep(str, n)` 返回字符串 str 的 n 个拷贝

- `string.sub(s, i [, j])` 截取字符串

- `string.gsub(mainString,findString,replaceString,num)` 在字符串中替换

- `string.find (str, substr, [init, [end]])` 在一个指定的目标字符串 str 中搜索指定的内容 substr，如果找到了一个匹配的子串，就会返回这个子串的起始索引和结束索引，不存在则返回 `nil`

- `string.gmatch(str, pattern)` 返回一个迭代器函数，每一次调用这个函数，返回一个在字符串 str 找到的下一个符合 pattern 描述的子串。如果参数 pattern 描述的字符串没有找到，迭代函数返回 `nil`

```lua
for word in string.gmatch("Hello Lua user", "%a+") 
do 
    print(word)
end
--[[
Hello
Lua
user
]]--
```

- `string.match(str, pattern[, init])` 寻找源字串str中的第一个配对，搜寻过程的起点默认为 1

```lua
string.match("I have 2 questions for you.", "%d+ %a+")
-- 2 questions
```

匹配模式直接用常规的字符串来描述，它用于模式匹配函数 `string.find`、`string.gmatch`、`string.gsub`、`string.match`

```lua
s = "Deadline is 30/05/1999, firm"
date = "%d%d/%d%d/%d%d%d%d"
print(string.sub(s, string.find(s, date)))    --> 30/05/1999

--[[
单个字符类匹配该类别中任意单个字符
模式匹配中有一些特殊字符 ( ) . % + - * ? [ ^ $
% 用作特殊字符的转义字符，用于所有的非字母的字符
单个字符类跟一个 '*'，将匹配零或多个该类的字符，总是匹配尽可能长的串
单个字符类跟一个 '+'，将匹配一或更多个该类的字符，总是匹配尽可能长的串
单个字符类跟一个 '-'，将匹配零或更多个该类的字符，总是匹配尽可能短的串
单个字符类跟一个 '?'，将匹配零或一个该类的字符，只要有可能，它会匹配一个
%n，这里的 n 可以从 1 到 9，这个条目匹配一个等于 n 号捕获物的子串
%bxy，x 和 y 是两个明确的字符，匹配以 x 开始 y 结束，且其中 x 和 y 保持平衡的字符串，即 x 和 y 对称的表达式

. 与任何字符配对
%a 与任何字母配对
%c 与任何控制符配对(例如\n)
%d 与任何数字配对
%l 与任何小写字母配对
%p 与任何标点(punctuation)配对
%s 与空白字符配对
%u 与任何大写字母配对
%w 与任何字母、数字配对
%x 与任何十六进制数配对
%z 与任何代表0的字符配对
[...] 与任何 [] 中包含的字符类配对，例如 [%w_] 与任何字母、数字, 或下划线符号 _ 配对
[^...] 与任何不包含在 [] 中的字符类配对，例如 [^%s] 与任何非空白字符配对

当上述的字符类用大写书写时, 表示与非此字符类的任何字符配对，%S 表示与任何非空白字符配对，'%A' 非字母的字符
]]--
```

### table

table 的创建是通过构造表达式来完成

最简单构造表达式是 `{}`，用来创建一个空表

也可以在表里添加一些数据，直接初始化表

```lua
-- 创建一个空的 table
local tbl1 = {}
 
-- 直接初始表
local tbl2 = {"apple", "pear", "orange", "grape"}
```

table 是一个关联数组数组，索引可以是数字或者是字符串

```lua
a = {}
a["key"] = "value"
key = 10
a[key] = 22
a[key] = a[key] + 11
```

表的默认初始索引一般以 1 开始

对 table 的索引使用方括号 `[]`，当索引是字符串时也提供了 `.` 操作

```lua
t[i]
t.i                 -- 当索引为字符串类型时的一种简化写法
```

- `table.concat (table [, sep [, start [, end]]])` 列出参数中指定 table 的数组部分从 start 位置到 end 位置的所有元素，元素间以指定的分隔符 sep 隔开

- `table.insert (table, [pos,] value)` 在 table 的指定位置插入值为 value 的一个元素，默认为数组部分末尾

- `table.remove (table [, pos])` 返回 table 数组部分位于 pos 位置的元素，其后的元素会被前移

- `table.sort (table [, comp])` 对给定的 table 进行升序排序

- `table.getn(table)` 获取 table 的长度，无论是使用 `#` 还是 `table.getn` 其都会在索引中断的地方停止计数，而导致无法正确取得 table 的长度

### function

函数可以存在变量里

```lua
function factorial1(n)
    if n == 0 then
        return 1
    else
        return n * factorial1(n - 1)
    end
end
print(factorial1(5))
factorial2 = factorial1
print(factorial2(5))
```

`function` 可以以匿名函数的方式进行传递

```lua
function testFun(tab,fun)
        for k ,v in pairs(tab) do
                print(fun(k,v));
        end
end


tab={key1="val1",key2="val2"};
testFun(tab,
function(key,val)--匿名函数
        return key.."="..val;
end
);
```

### userdata

`userdata` 是一种用户自定义数据，用于表示一种由应用程序或 C/C++ 语言库所创建的类型

可以将任意 C/C++ 的任意数据类型的数据（通常是 `struct` 和指针）存储到 Lua 变量中调用

## 变量

Lua 变量有三种类型：全局变量、局部变量、表中的域

Lua 中的变量全是全局变量，哪怕是语句块或是函数里，除非用 `local` 显式声明为局部变量

局部变量的作用域为从声明位置开始到所在语句块结束

应该尽可能的使用局部变量，可以避免命名冲突和加快访问速度

```lua
a = 5               -- 全局变量
local b = 5         -- 局部变量

function joke()
    c = 5           -- 全局变量
    local d = 6     -- 局部变量
end

joke()
print(c,d)          --> 5 nil

do
    local a = 6     -- 局部变量
    b = 6           -- 对局部变量重新赋值
    print(a,b);     --> 6 6
end

print(a,b)      --> 5 6
```

Lua 可以对多个变量同时赋值，变量列表和值列表的各个元素用逗号分开，赋值语句右边的值会依次赋给左边的变量

```lua
a, b = 10, 2*x       -->       a=10; b=2*x
```

Lua 会先计算右边所有的值然后再执行赋值操作

```lua
x, y = y, x                     -- swap 'x' for 'y'
```

对多个变量同时赋值，不会进行变量传递，仅做值传递

```lua
a, b = 0, 1
a, b = a+1, a+1
print(a,b)               --> 1   1
a, b = 0, 1
a, b = b+1, b+1
print(a,b)               --> 2   2
a, b = 0, 1
a = a+1
b = a+1
print(a,b)               --> 1   2
```

## if

```lua
if(xx)
then
   --[ 在布尔表达式为 true 时执行的语句 --]
end

if(xx)
then
   --[ 布尔表达式为 true 时执行该语句块 --]
else
   --[ 布尔表达式为 false 时执行该语句块 --]
end

if(xx)
then
   --[ 在布尔表达式 1 为 true 时执行该语句块 --]

elseif(yy)
then
   --[ 在布尔表达式 2 为 true 时执行该语句块 --]

elseif(zz)
then
   --[ 在布尔表达式 3 为 true 时执行该语句块 --]
else 
   --[ 如果以上布尔表达式都不为 true 则执行该语句块 --]
end
```

## while

```lua
while(condition)
do
   statements
end
```

## for

for语句有两大类，数值 `for` 循环和泛型 `for` 循环

### 数值循环

- `var` 从 `exp1` 变化到 `exp2`，每次变化以 `exp3` 为步长递增 `var`

- `exp3` 是可选的，如果不指定，默认为 1

```lua
for var=exp1,exp2,exp3 do  
    <执行体>  
end

-- f(x) 只计算一次
for i=1,f(x) do
    print(i)
end
 
for i=10,1,-1 do
    print(i)
end
```

### 范型循环

通过一个迭代器函数来遍历所有值

```lua
a = {"one", "two", "three"}
for i, v in ipairs(a) do
    print(i, v)
end 
```

`pairs` 和 `ipairs` 都能遍历集合

- `ipairs` 仅仅遍历值，按照索引升序遍历，索引中断停止遍历，只能遍历到集合中出现的第一个不是整数的 key

```
local tabFiles = {
        [1] = "test2",
        [6] = "test3",
        [4] = "test1"
    }

-- 输出 test2，在 key 等于 2 处断开
for k, v in ipairs(tabFiles) do    
    print(k, v)
end

local tabFiles = {
    [2] = "test2",
    [6] = "test3",
    [4] = "test1"
}

-- 什么都没输出，因为控制变量初始值是按升序来遍历的
-- 当 key 为 1 时，value 为 nil，此时便停止了遍历
for k, v in ipairs(tabFiles) do  
    print(k, v)
end
```

- `pairs` 能遍历集合的所有元素

```lua
local tabFiles = {"alpha", "beta", [3] = "no", ["two"] = "yes"}  

-- 输出前三个，因为第四个 key 不是整数
for i,v in ipairs(tabFiles ) do    
    print( tabFiles [i] )   
end   
  
for i,v in pairs(tabFiles ) do    --全部输出   
    print( tabFiles [i] )   
end 
```

泛型 `for` 在自己内部保存迭代函数，实际上它保存三个值：迭代函数、状态常量、控制变量

1. 初始化，计算 `in` 后面表达式的值，表达式应该返回泛型 `for` 需要的三个值：迭代函数、状态常量、控制变量

2. 将状态常量和控制变量作为参数调用迭代函数

3. 将迭代函数返回的值赋给变量列表

4. 如果返回的第一个值为 `nil` 循环结束，否则执行循环体

5. 回到第二步再次调用迭代函数

## repeat...until

`repeat...until` 循环的条件语句在当前循环结束后判断

```lua
repeat
   statements
until( condition)

a = 10
repeat
   print("a的值为:", a)
   a = a + 1
until( a > 15 )
```

## break

退出当前循环或语句

```lua
a = 10
while( a < 20 )
do
   print("a 的值为:", a)
   a=a+1
   if( a > 15)
   then
      --[ 使用 break 语句终止循环 --]
      break
   end
end
```

## goto

```lua
:: Label ::
goto label

local a = 1
::label:: print("--- goto label ---")

a = a+1
if a < 3 then
    goto label 
end
```

## function

```lua
optional_function_scope function function_name( argument1, argument2, argument3..., argumentn)
    function_body
    return result_params_comma_separated
end
```

- `optional_function_scope` 可选，标明是全局函数还是局部函数，未设置该参数默认为全局函数，如果需要设置函数为局部函数需要使用关键字 `local`

- `function_name` 指定函数名称

- `argument1, argument2, argument3..., argumentn` 函数参数

- `result_params_comma_separated` 函数返回值，可以返回多个值，每个值以逗号隔开

```lua
function max(num1, num2)
   if (num1 > num2) then
      result = num1;
   else
      result = num2;
   end
   return result;
end
```

可以将函数作为参数传递给函数

```lua
myprint = function(param)
   print("这是打印函数 -   ##",param,"##")
end

function add(num1,num2,functionPrint)
   result = num1 + num2
   -- 调用传递的函数参数
   functionPrint(result)
end
myprint(10)
-- myprint 函数作为参数传递
add(2,5,myprint)
```

函数可以接受可变数目的参数，在函数参数列表中使用三点 `...` 表示函数有可变的参数

```lua
function add(...)  
local s = 0  
  for i, v in ipairs{...} do   --> {...} 表示一个由所有变长参数构成的数组  
    s = s + v  
  end  
  return s  
end  
print(add(3,4,5,6,7))  --->25

function average(...)
   result = 0
   local arg={...}    --> arg 为一个表，局部变量
   for i,v in ipairs(arg) do
      result = result + v
   end
   print("总共传入 " .. #arg .. " 个数")
   return result/#arg
end
print("平均值为",average(10,5,3,4,5,6))

function fwrite(fmt, ...)  ---> 固定的参数fmt
    return io.write(string.format(fmt, ...))    
end
fwrite("runoob\n")       --->fmt = "runoob", 没有变长参数。  
fwrite("%d%d\n", 1, 2)   --->fmt = "%d%d", 变长参数为 1 和 2
```

通常在遍历变长参数的时候只需要使用 `{…}`，然而变长参数可能会包含一些 `nil`，可以用 `select` 函数来访问变长参数

`select('#', …)` 返回可变参数的长度

`select(n, …)` 用于返回从起点 n 开始到结束位置的所有参数列表

```lua
function f(...)
    a = select(3,...)  -->从第三个位置开始，变量 a 对应右边变量列表的第一个参数
    print (a)
    print (select(3,...)) -->打印所有列表参数
end

f(0,1,2,3,4,5)
```

## 运算符

- `+` 加

- `-` 减

- `*` 乘

- `/` 除，带小数点

- `%` 取余

- `^` 乘幂

- `-` 负号

- `//` 整除运算符

- `==` 等于

- `～=` 不等于

- `>` 大于

- `<` 小于

- `>=` 大于等于

- `<=` 小于等于

- `and` 逻辑与

- `or` 逻辑或

- `not` 逻辑非

- `..` 连接两个字符串

- `#` 返回字符串或表的长度

优先级

```lua
^
not    - (unary)
*      /       %
+      -
..
<      >      <=     >=     ~=     ==
and
or
```

## 数组

索引值是以 1 为起始，但也可以指定 0 和负索引

```lua
array = {"1", "2"}

for i= 0, 2 do
   print(array[i])
end
-- nil
-- "1"
-- "2"

array = {}

for i= -2, 2 do
   array[i] = i *2
end

for i = -2,2 do
   print(array[i])
end
-- -4
-- -2
-- 0
-- 2
-- 4
```

支持多维数组

```lua
array = {}
for i=1,3 do
   array[i] = {}
      for j=1,3 do
         array[i][j] = i*j
      end
end

for i=1,3 do
   for j=1,3 do
      print(array[i][j])
   end
end
```
