# XorAndSum
作者：赵晟宇

关键词：线性基 高斯消元

## 题目简述
给定一个长度为$$n$$的整数序列$$number_i (0 \leq i < n)$$。每次操作选择两个整数$$i, j (0 \leq i, j < n; i \neq j)$$，将$$number_i$$修改为$$number_i$$与$$number_j$$的二进制异或，而$$number_j$$不变。不限操作次数，求序列中所有数之和的最大值。

$$1 \leq n \leq 50$$
$$0 \leq number_i \leq 10^{15}$$

## 算法


时间复杂度$$O(n^2)$$，空间复杂度$$O(n)$$。