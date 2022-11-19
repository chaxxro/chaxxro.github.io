# marco

```cmake
set(var "ABC")

macro(Moo arg)
    message("arg = ${arg}")  # 输出原值 ABC
    set(arg "abc")
    message("# After change the value of arg.")
    message("arg = ${arg}")  # 输出原值 ABC
endmacro()
```

在宏定义体中，需要引用参数的话，只能写 `${arg}`

宏定义会将所有 `${arg}` 的地方进行直接简单粗暴地替换，因此，宏定义中的 `set` 方法试图改变宏定义中传进来的参数 `arg` 是不可能的

宏的 `ARGN`、`ARGV` 等内部变量不能直接在 `if` 语句和 `foreach` 语句中使用


|变量|说明
|-|-|
ARGV#|ARGV0 为第一个参数，ARGV1 为第二个参数，依次类推
ARGV|定义宏（函数）时参数为 2 个，实际传了 4 个，则 ARGV 代表实际传入的两个
ARGN|定义宏（函数）时参数为 2 个，实际传了 4 个，则ARGN代表剩下的 2 个
ARGC|实际传入的参数的个数