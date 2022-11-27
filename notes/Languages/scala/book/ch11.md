# List

列表是不可变的，即列表的元素不能通过赋值改变

列表的结构是递归的

## 构建列表

所有的列表都构建自两个基础单元 `:Nil` 和 `::`

中缀操作符 `::` 表示在列表前追加元素，且由于 `::` 是右结合，所以 `A::B::C` 可以翻译成 `A::(B::C)`

```scala
val nums = 1 :: 2 :: 3 :: Nil
```

## List 协变

Scala 的列表类型是协变的，即对于 `S` 和 `T`，当 `S` 是 `T` 的子类型时，`List[S]` 也是 `List[T]` 的子类型

因为 `Object` 是顶类型，所以 `List[Object]` 是所有 `List[T]` 的父类型

因为 `Nothing` 是底类型，所以 `List[Nothing]` 是所有 `List[T]` 的子类型

空列表的类型是 `List[Nothing]`

## 基本操作

对列表的所有操作都可以用三项表示：

- `head` 返回列表的第一个元素

- `tail` 返回除第一个元素外的其他所有元素

- `isEmpty` 返回是否为空列表

```scala
// 插入排序
def isort(xs: List[Int]): List[Int] = {
    if (xs.isEmpty) Nil
    else insert(xs.head, isort(xs.tail))
}

def insert(x: Int, xs: List[Int]): List[Int] = {
    if (xs.isEmpty || x <= xs.head) x :: xs
    else xs.head :: insert(x, xs.tail)
}
```

## 列表模式

列表可以用模式匹配解开，可以逐一对应到列表表达式

```scala
val List(a, b, c) = nums
// a == 1
// b == 2
// c == 3
val d :: e :: f = nums
// d == 1
// e == 2
// f == 3
```

```scala
// 使用模式匹配的插入排序
def isort(xs: List[Int]): List[Int] = xs match {
    case List() => List()
    case x :: tail => insert(x, isort(tail))
}

def insert(x: Int, xs: List[Int]): List[Int] = xs match {
    case List() => List()
    case y :: tail => {
        if (x <= y) x :: xs
        else y :: insert(x, tail)
    }
}
```

## 初阶方法

`:::` 接受两个列表参数

```scala
List(1, 2) ::: List(3, 4)
```

`length` 获取列表长度

`last` 获取列表最后一个元素，`init` 获取除最后一个元素的所有元素，`init` 和 `last` 需要遍历整个列表，耗时跟长度成正比

`reverse` 创建一个原列表反转后的新列表

`take` 获取列表前 n 个元素，`drop` 获取除前 n 个元素外的所有元素

`splitAt` 将列表从指定下标位置切开，返回两个列表组成的 `Tuple`，等价于 `(xs.take(n), xs.drop(n))`

`apply` 支持从任意位置选取元素，`list.apply(2)` 等价于 `list.drop(n).head`

`indices` 返回指定列表所有有效下标的列表

`flatten` 将列表的列表扁平化，返回单个列表

`zip` 接受两个列表，返回一个由 `Tuple` 组成的列表，将两个列表的元素组合起来

`zipWithIndex` 返回元素与下标组成的列表

`unzip` 将 `Tuple` 组成的列表还原成两个列表

```scala
// 归并排序
def msort[T](less: (T, T) => Boolean)(xs: List[T]): List[T] = {
    def merge(xs: List[T], ys: List[T]): List[T] = (xs, ys) match {
        case (Nil, _) => ys
        case (_, Nil) => xs
        case (x :: xs1, y :: ys1) => {
            if (less(x, y)) x :: merge(xs1, ys)
            else y :: merge(xs, ys1)
        }
    }

    val n = xs.length / 2
    if (n == 0) xs
    else {
        val (ys, zs) = xs.splitAt(n)
        merge(msort(less)(ys), msort(less)(zs))
    }
}
```

## 高阶方法

`map` 将 `List[T]` 转换成 `List[f(T)]`

`flatMap` 要求入参的操作元返回一个元素列表，并将所有结果拼接成一个列表

`filter` 接受 `T => Boolean` 的前提条件函数，返回满足条件的列表

`partition` 与 `filter` 类似，但返回 `(List, List)`，等价于 `(xs.filter(p), xs.filter(!p(_)))`

`find` 返回第一个满足条件的元素，返回 `Option[T]`

`foldLeft(z)(op)`、`foldRight(z)(op)` 折叠列表，`z` 为起始值，`op` 为二元操作符

```scala
// 0 + a + b + ...
def sum(xs: List[Int]): Int = xs.foldLeft(0)(_ + _)
```

`sortWith` 对列表进行排序