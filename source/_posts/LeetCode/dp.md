---
toc:
  enable: true
  number: false
  max_depth: 3
title: dp
date: 2023-04-01 16:01:49
tags: LeetCode
categories: LeetCode
---

## lc5

```cpp
/*
1. dp
dp[i][j] : s[i] ~ s[j] 是否是回文串

2. 从中间开始找
分两种情况: s[index] 和 s[index] ~ s[index + 1]
s[index - step] ~ s[index + step]:  
s[index - step] ~ s[index + 1 + step]
*/
```

[题目](https://leetcode.com/problems/longest-palindromic-substring/)

[分析](https://www.bilibili.com/video/BV18J411j7Pb?from=search&seid=13947515736860821639)

## lc10

```cpp
/*
1. 以长度作为 dp 数组下表，避免索引下表越界问题
2. 特殊处理情况只有 s 长度 0
3. 状态转移中只依赖 s[i - 1] 的结果，可以做内存优化
*/
```
[分析](https://www.cnblogs.com/grandyang/p/4401196.html)
[题目](https://leetcode.com/problems/wildcard-matching)

## lc32

```cpp
/*
括号题主要是用栈

dp[i] 表示以 i 下标结束的长度，l 表示当前有效括号长度
dp[i] = l + dp[i - l + 1 - 1]
*/
```

[题目](https://leetcode.com/problems/longest-valid-parentheses/)

## lc44

```cpp
/*
dp[i][j] 表示 s 中前 i 个字符组成的子串和 p 中前 j 个字符组成的子串是否能匹配

dp[0][0] = true

当 s 为空，p 为连续的星号时，由于星号是可以代表空串的，所以只要 s 为空，那么连续的星号的位置都应该为 true，所以先将连续星号的位置都赋为 true

若 p 中第 j 个字符是星号，由于星号可以匹配空串，所以如果 p 中的前 j-1 个字符跟 s 中前 i 个字符匹配成功了的话（dp[i][j - 1]），则 dp[i][j] 也能为 true；由于型号可以匹配任意字符串，若 p 中的前 j 个字符跟 s 中的前 i-1 个字符匹配成功了的话（dp[i - 1][j]），则 dp[i][j] 也能为 true
*/
```
[分析](https://www.cnblogs.com/grandyang/p/4461713.html)
[题目](https://leetcode.com/problems/regular-expression-matching/)

## lc72

{% asset_img 01.png %}

```cpp
/*
dp[i][j] : word1[0 ~ i - 1] to word2[0 ~ j - 1]

dp[i][j] = 
            i if j == 0
            j if i == 0
            dp[i - 1][j - 1] if word1[i - 1] == word2[j - 1]
            min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1 // 删 改 插入
*/
```

[题目](https://leetcode.com/problems/edit-distance/)

[分析](https://www.youtube.com/watch?v=Q4i_rqON2-E)