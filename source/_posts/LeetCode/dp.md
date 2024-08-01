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

dp[i][j] =  i if j == 0
            j if i == 0
            dp[i - 1][j - 1] if word1[i - 1] == word2[j - 1]
            min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1 // 删 插入 改

[abb, ac] 执行删操作后变成 [ab, ac]，对应 dp[i - 1][j]
[abb, ac] 执行改操作后变成 [abc, ac]，对应 dp[i - 1][j - 1]
[abb, ac] 执行插入操作后变成 [abbc, ac]，对应 dp[i][j - 1]
*/
```

[题目](https://leetcode.com/problems/edit-distance/)

[分析](https://www.youtube.com/watch?v=Q4i_rqON2-E)

## lc95、lc96

```cpp
/*
将区间  [1, n] 当作一个整体，然后需要将其中的每个数字都当作根结点，其划分的左右两个子区间作为子节点
G(n) 表示 1~n 有多少种 BST，F(i, n) 表示以 i 为根结点有多少 BST
G(n) = F(1, n) + F(2, n) + ... + F(n, n)
F(i, n) = G(i - 1) * G(n - i)
G(n) = G(0) * G(n-1) + G(1) * G(n-2) + ... + G(n-1) * G(0) 
*/
```

[题目](https://leetcode.com/problems/unique-binary-search-trees/description/)

[题目](https://leetcode.com/problems/unique-binary-search-trees-ii/)

## lc97

```cpp
/*
dp[i][j] 表示 s1 i 长，s2 j 长可以组成 s3 i+j 长
dp[0][0] = true
dp[0][i] = dp[0][i - 1] && s2[i - 1] == s3[i - 1]
dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1]
dp[i][j] = (dp[i - 1][j] && s1[i + j - 1] == s3[i - 1]) || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1])
*/
```

[题目](https://leetcode.com/problems/interleaving-string/description/)

## lc121、lc122、lc123、lc188

```cpp
/*
121
只有一次买入卖出机会
找到与之前价格的最大差值即可

122
任意买入卖出，但不能同时拥有多只股票
将所有差值累加即可

123 最多两次交易，且不能同时拥有多只股票

188 最多 k 次交易，且不能同时拥有多只股票
dp[i][j] 表示第 i 天经过至少 j 次操作的最大利润
当第 i 天不操作时，dp[i][j] = dp[i - 1][j]
当第 i 天卖出股票时，dp[i][j] = dp[m][j - 1] + prices[i - 1] - prices[m] = prices[i - 1] - (prices[m] - dp[m][j- 1])
可以缓存 prices[m] - dp[m][j - 1] 来避免重复计算

*/
```

[题目](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

[题目](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/)

[题目](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)

[题目](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)

## lc139

```cpp
/*
1. 记忆化递归
2. dp
l 表示字符串长度
dp[l] = dp[j] && dict.count(s.substr(j, l - j)) != 0
*/
```

[题目](https://leetcode.com/problems/word-break/description/)

## lc300

```cpp
/*
方法一：
dp[i]：下标为 i 元素的最长递增子序列

方法二：
dp[i]：长度为 i 的最长递增子序列最大元素
当不同递增序列长度相同时，序列最大值中的最小值更佳，所以保存最大值中的最小值

方法三：
在方法二中，dp 数组是单调递增的，所以可以使用二分的方法
*/ 
```

[题目](https://leetcode.com/problems/longest-increasing-subsequence/)

[分析](https://www.bilibili.com/video/BV1Wf4y1y7ou)

## lc312

```cpp
/*
dp[i][j] = maxCoins(nums[i] ~ nums[j])
在 i ~ j 中，最后打 k 处的气球
dp[i][j] = max(dp[i][k - 1] + nums[i - 1] * nums[k] * nums[j + 1] + dp[k + 1][j]), i <= k <= j 
*/
```

[题目](https://leetcode.com/problems/burst-balloons/)

[分析](https://www.youtube.com/watch?v=z3hu2Be92UA&t=700s)

## lc375

```cpp
/*
dp[i][j] 表示在 i~j 中猜中一个数的最小花费
从 i~j 中挑选 k，每次都考虑最差的情况来保证最小花费 k + max(dp[i][k - 1], dp[k + 1][j])
dp[i][j] = min(k + max(dp[i][k - 1], dp[k + 1][j])), k = i~j
*/
```

[题目](https://leetcode.com/problems/guess-number-higher-or-lower-ii/description/)

## lc410

```cpp
/*
dp[i][j] : nums[0] ~ nums[j] split i groups

dp[1][j] = sum(nums[0] ~ nums[j])
dp[i][j] = min(max(dp[i - 1][k], sum(nums[j] ~ nums[k + 1])))
*/
```

[题目](https://leetcode.com/problems/split-array-largest-sum/)

[分析](https://www.youtube.com/watch?v=_k-Jb4b7b_0&t=668s)

## lc416

```cpp
/*
背包问题一般都可以进行状态压缩，压缩后需要反向更新状态

dp[i] : sum(subset(...)) == i
*/
```

[题目](https://leetcode.com/problems/partition-equal-subset-sum/)

[分析](https://www.youtube.com/watch?v=r6I-ikllNDM&t=382s)

## lc818

[题目](https://leetcode.com/problems/race-car/description/)

[分析](https://www.youtube.com/watch?v=HzlEkUt2TYs)

[分析](https://www.youtube.com/watch?v=Z39RHxb2Lew)

## lc894

[题目](https://leetcode.com/problems/all-possible-full-binary-trees/description/)

## lc926

```cpp
/*
1.
prefix + suffix
l[i] : filps of s[0] ~ s[i] all 0
r[i] : filps of s[i] ~ s[n - 1] all 1
l[i] = l[i - 1] + s[i] == 1
r[i] = r[i + 1] + s[i] == 0
ans = min(l[i - 1] + r[i], l[n - 1], r[0])

2.
dp0[i]：表示反转 s[0]~s[i] 使其满足条件且最后一个是 0 
dp1[i]：表示反转 s[0]~s[i] 使其满足条件且最后一个是 1

dp0[i] = dp0[i - 1] if s[i] == 0
dp0[i] = dp0[i - 1] + 1 if s[i] == 1

dp1[i] = min(dp0[i - 1], dp1[i - 1]) + 1 if s[i] == 0
dp[i] = min(dp0[i - 1], dp1[i - 1]) if s[i] == 1
*/
```

[题目](https://leetcode.com/problems/flip-string-to-monotone-increasing/)

[分析](https://www.youtube.com/watch?v=D8xa8ZMV7AI)

## lc1000

[题目](https://leetcode.com/problems/minimum-cost-to-merge-stones/description/)

[分析](https://www.youtube.com/watch?v=FabkoUzs64o)

## lc1043

[题目](https://leetcode.com/problems/partition-array-for-maximum-sum/description/)

## lc1143

```cpp
/*
dp[i][j] : text[0 ~ i] text[0 ~j] LCS

if text[i] == text[j] then dp[i][j] = dp[i - 1][j - 1] + 1
else dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1])
*/
```

[题目](https://leetcode.com/problems/longest-common-subsequence/)

## lc1278

```cpp
/*
dp[i][j] : s[0 ~ i - 1] splite j group

dp[i][j] = min(dp[k][j - 1] + cast(k, i - 1)) j - 2 < k < i - 2
*/
```

[题目](https://leetcode.com/problems/palindrome-partitioning-iii/)

[分析](https://www.youtube.com/watch?v=kD6ShM6jr3g)

## lc1349

```cpp
/*
利用行状态做 DP
dp[i][s]：第 i 行学生分布状态为 s 时的最多人数
dp[i + 1][s] = max(dp[i][t] + popcount(s))
这里 s 需要与 t 是合法关系

通过位运算取一个数的二进制子集
x = v
while x:
    x = (x - 1) & v
*/
```

[题目](https://leetcode.com/problems/maximum-students-taking-exam/)

[分析](https://www.youtube.com/watch?v=QJvCYx1eGxE)

## lc1411

```cpp
/*
利用行的状态做 DP
一行格子涂装总共有 27 中方式
dp[i][p] 表示第 i 行用 p 这种方式涂装的次数
dp[i + 1][q] = sum(dp[i][p]) 其中 q 与 p 不冲突
*/
```

[题目](https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/)

[分析](https://www.youtube.com/watch?v=LwD9UIDIvHE)

## lc1416

```cpp
/*
递归形式：
int helper(string s) {
    if(s.empty() == 0) return 1;
    if(s[0] == '0') return 0;
    int ans = 0;
    for(int i = 1; i < s.length(); ++i) {
        int num = stoi(s.substr(0, i));
        if(num > K) break;
        ans += (ans + helper(s.substr(i))) % kmod;
    }
    return ans;
}
使用 hash 记忆化后仍超时

dp[i] : s[i ~ n] cnt
dp[i] = sum(dp[j]) j : i ~ n
*/
```

[题目](https://leetcode.com/problems/restore-the-array//)

[分析](https://www.youtube.com/watch?v=mdUTRI2FMtU)

## lc1449

[题目](https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/submissions/)

[分析](https://www.youtube.com/watch?v=J43N1o1XhqE)

## lc1458

[题目](https://leetcode.com/problems/max-dot-product-of-two-subsequences/description/)

## lc1653

```cpp
/*
dp[i] 表示 s[0~i] 平衡的删除操作
*/
```

[题目](https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/)

[分析](https://github.com/doocs/leetcode/blob/main/solution/1600-1699/1653.Minimum%20Deletions%20to%20Make%20String%20Balanced/README.md)

## lc1655

Bitmask + subsets + DP

```cpp
/*
dp[mask][i]: 选择客户为 mask 时，能否用前 i 组数满足

dp[mask][i] = any(
    sums(subset) <= freq[i] and dp[mask^subset][i - 1]
)
*/
```

[题目](https://leetcode.com/problems/distribute-repeating-integers/)

[分析](https://www.bilibili.com/video/BV1qt4y1a7Lm)