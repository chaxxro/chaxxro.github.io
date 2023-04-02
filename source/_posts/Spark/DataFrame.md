---
toc:
  enable: true
  number: false
  max_depth: 3
title: DataFrame
date: 2023-04-02 15:23:13
tags: Spark
categories: Spark
---

RDD 中的 `map`、`mapPartitions`、`filter`、`flatMap` 算子都是高阶函数，都需要一个辅助函数 `f` 来作为形参，通过 `f` 来完成计算

对于 Spark 来说，辅助函数 `f` 是透明的，Spark Core 只能把函数 `f` 以闭包的形式打发到 Executor，没办法做更多的优化

DataFrame 与 RDD 一样，都是用来封装分布式数据集的

DataFrame 是携带数据模式（Data Schema）的结构化数据，而 RDD 是不携带 Schema 的分布式数据集

因为有了 Schema 提供明确的类型信息，Spark 才能有针对性地设计出更紧凑的数据结构，从而大幅度提升数据存储与访问效率

DataFrame 算子的表达能力却很弱，它定义了一套 DSL（Domain Specific Language） 算子

DataFrame 的算子大多数都是标量函数，它们的形参往往是结构化二维表的数据列

## 从 Driver 创建 DataFrame

在 Driver 端，Spark 可以直接从数组、元组、映射等数据结构创建 DataFrame

### createDataFrame 方法

`createDataFrame` 方法有两个形参，第一个参数是 `RDD[Row]`，第二个参数是 `Schema`

### toDF 方法

通过 `spark.implicits` 中的隐式方法，可以不需要创建 `Schema` 直接由 RDD 或 Seq 创建 DataFrame

## 从文件系统创建 DataFrame

使用 read API 创建 DataFrame，开发者只需要调用 SparkSession 的 read 方法，同时通过 `format`、`option` 和 `load` 提供文件格式、加载选项和文件路径