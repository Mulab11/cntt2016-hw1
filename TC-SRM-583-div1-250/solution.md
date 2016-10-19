# TravelOnMars
作者：罗煜楚

关键词：最短路 Bfs
## 题目简述
有n个点成环形排列，编号从0到n-1，i号点有一个范围值range[i]，表示i号与距离i号点不超过range[i]的所有点之间都有一条边，编号为x和y的两个点间的距离的定义为$$min(\left|x-y\right|, n - \left|x-y\right|)$$，求从编号为St的点到编号为Ed的点的最少需要经过的边数。

$$n \leqslant 50$$ , $$range[i] \leqslant 50 (0\leqslant i < 50)$$
## 算法
数据范围很小，可以直接按照题意建图，由于边没有权值，或者说权值都为1,所以直接使用Bfs即广度优先搜索搜出最短路径即可