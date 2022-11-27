# 面向对象

Lua 中最基本的结构是 `table`，所以需要用 `table` 来描述对象的属性

Lua 中的 `function` 可以用来表示方法，可以通过 `metetable` 模拟继承

```lua
Account = {balance = 0}
function Account.withdraw (v)
    Account.balance = Account.balance - v
end
```