# 元表

元表允许改变 `table` 的行为，每个行为关联了对应的元方法

- `setmetatable(table,metatable)` 指定 `table` 设置元表，如果元表中存在 `__metatable` 键值，`setmetatable` 会失败

- `getmetatable(table)` 返回对象的元表

```lua
mytable = {}                          -- 普通表
mymetatable = {}                      -- 元表
setmetatable(mytable,mymetatable)     -- 把 mymetatable 设为 mytable 的元表
```

## __index 元方法

当通过键来访问 `table` 的时候，如果这个键没有值，那么 Lua 就会寻找该 `table` 的 `metatable` 中的 `__index` 键

如果 `__index` 包含一个表格，Lua 会在表格中查找相应的键

```lua
other = { foo = 3 }
t = setmetatable({}, { __index = other })
t.foo  -- 3
```

如果 `__index` 包含一个函数的话，Lua 就会调用那个函数，`table` 和键会作为参数传递给函数

```lua
mytable = setmetatable({key1 = "value1"}, {
  __index = function(mytable, key)
    if key == "key2" then
      return "metatablevalue"
    else
      return nil
    end
  end
})

print(mytable.key1,mytable.key2)
```

Lua 查找一个表元素时的规则：

1. 在表中查找，如果找到，返回该元素，找不到则继续

2. 判断该表是否有元表，如果没有元表，返回 nil，有元表则继续

3. 判断元表有没有 `__index` 方法，如果 `__index` 方法为 `nil`，则返回 `nil`；如果 `__index` 方法是一个表，则重复 1、2、3；如果 `__index` 方法是一个函数，则返回该函数的返回值

## __newindex 元方法

`__newindex` 元方法用来对表更新，`__index` 用来对表访问

当给表的一个缺少的索引赋值，解释器就会查找 `__newindex` 元方法，如果存在则调用这个函数而不进行赋值操作

```lua
mymetatable = {}
mytable = setmetatable({key1 = "value1"}, { __newindex = mymetatable })

print(mytable.key1)     -- value1

mytable.newkey = "新值2"
print(mytable.newkey,mymetatable.newkey)    -- nil    新值2

mytable.key1 = "新值1"
print(mytable.key1,mymetatable.key1)      -- 新值1    nil
``` 

## 操作符

`__add`	对应的运算符 '+'

`__sub`	对应的运算符 '-'

`__mul`	对应的运算符 '*'

`__div`	对应的运算符 '/'

`__mod`	对应的运算符 '%'

`__unm`	对应的运算符 '-'.

`__concat`	对应的运算符 '..'

`__eq`	对应的运算符 '=='

`__lt`	对应的运算符 '<'

`__le`	对应的运算符 '<='

## __call 元方法

`__call` 元方法在 Lua 调用一个值时调用

```lua
function table_maxn(t)
    local mn = 0
    for k, v in pairs(t) do
        if mn < k then
            mn = k
        end
    end
    return mn
end

-- 定义元方法__call
mytable = setmetatable({10}, {
  __call = function(mytable, newtable)
        sum = 0
        for i = 1, table_maxn(mytable) do
                sum = sum + mytable[i]
        end
    for i = 1, table_maxn(newtable) do
                sum = sum + newtable[i]
        end
        return sum
  end
})
newtable = {10,20,30}
print(mytable(newtable)) . -- 70
```

## __tostring 元方法

`__tostring` 元方法用于修改表的输出行为

```lua
mytable = setmetatable({ 10, 20, 30 }, {
  __tostring = function(mytable)
    sum = 0
    for k, v in pairs(mytable) do
                sum = sum + v
        end
    return "表所有元素的和为 " .. sum
  end
})
print(mytable)    -- 60
```