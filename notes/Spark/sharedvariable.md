# 共享变量

按照创建与使用方式的不同，Spark 提供了两类共享变量，分别是广播变量和累加器

## 广播变量

通过调用 SparkContext 下的 broadcast API 即可完成广播变量的创建

```scala
val list: List[String] = List("Apache", "Spark")
val bc = sc.broadcast(list)

// 读取广播变量内容
bc.value
```

如果变量在 Driver 端创建，且不是分布式数据集，则在分布式计算的过程中，Spark 需要把变量分发给每一个分布式任务

如果 RDD 并行度较高、或是变量的尺寸较大，那么重复的内容分发就会引入大量的网络开销与存储开销，而这些开销会大幅削弱作业的执行性能

Driver 端变量的分发是以 Task 为粒度的，系统中有多少个 Task，变量就需要在网络中分发多少次

在同一个 Executor 内部，多个不同的 Task 多次重复地缓存了同样的内容拷贝，这对内存资源是一种巨大的浪费

在使用广播变量之后，变量分发的粒度变成了以 Executors 为单位，同一个 Executor 内多个不同的 Tasks 只需访问同一份数据拷贝即可

换句话说，变量在网络中分发与存储的次数，从 RDD 的分区数量，锐减到了集群中 Executors 的个数

广播变量由 Driver 端定义并初始化，各个 Executors 以只读（Read only）的方式访问广播变量携带的数据内容

## 累加器

累加器的主要作用是全局计数

累加器也是在 Driver 端定义的，但它的更新是通过在 RDD 算子中调用 add 函数完成的，在应用执行完毕之后，在 Driver 端调用累加器的 value 函数，就能获取全局计数结果

```scala
// 定义Long类型的累加器
val ac = sc.longAccumulator("Empty string")

ac.value
```

SparkContext 提供了 longAccumulator、doubleAccumulator 和 collectionAccumulator

collectionAccumulator 允许定义集合类型的累加器，相比数值类型，集合类型可以为业务逻辑的实现，提供更多的灵活性和更大的自由度

累加器也是由 Driver 定义的，但 Driver 并不会向累加器中写入任何数据内容，累加器的内容更新，完全是由各个 Executors 以只写（Write only）的方式来完成，而 Driver 仅以只读的方式对更新后的内容进行访问