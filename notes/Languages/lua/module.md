# 模块

Lua 的模块是由变量、函数等已知元素组成的 `table`，因此创建一个模块很简单，就是创建一个 `table`，然后把需要导出的常量、函数放入其中，最后返回这个 `table` 就行

```lua
-- 文件名为 module.lua
-- 定义一个名为 module 的模块
module = {}
 
-- 定义一个常量
module.constant = "这是一个常量"
 
-- 定义一个函数
function module.func1()
    io.write("这是一个公有函数！\n")
end
 
local function func2()
    print("这是一个私有函数！")
end
 
function module.func3()
    func2()
end
 
return module
```

Lua 提供了一个名为 require 的函数用来加载模块

```lua
require("<模块名>")
require "<模块名>"
```

执行 `require` 后会返回一个由模块常量或函数组成的 `table`，并且还会定义一个包含该 `table` 的全局变量

```lua
require("module")
print(module.constant) 
module.func3()

-- 给加载的模块定义一个别名变量
local m = require("module")
print(m.constant) 
m.func3()
```

对于自定义的模块，模块文件不是放在哪个文件目录都行，函数 `require` 有它自己的文件路径加载策略，它会尝试从 Lua 文件或 C 程序库中加载模块

`require` 用于搜索 Lua 文件的路径是存放在全局变量 package.path 中，当 Lua 启动后，会以环境变量 `LUA_PATH` 的值来初始这个环境变量

如果没有找到该环境变量，则使用一个编译时定义的默认路径来初始化

## C 包

C 包在使用以前必须首先加载并连接，在大多数系统中最容易的实现方式是通过动态连接库机制

`loadlib` 的函数内提供了所有的动态连接的功能，然而它并不打开库

```lua
local path = "/usr/local/lua/lib/libluasocket.so"
local f = loadlib(path, "luaopen_socket")
```