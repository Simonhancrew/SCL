## 算法模板

Standar Code Library，记录算法的模板和算法学习。

### [bit](Bit/)

+ lowbit

### [DataStruct](Datastruct/):

常见的数据结构的数组实现

### [Graph](Graph/)

搜索，最短路，最小生成树

### [greedyAlgo](greedyAlgorithm/)

贪心算法的套路

### [Math](Math/)

各种数论问题

### [random](Random/)

随机处理

### [Search](Search/)

搜索（整数二分和浮点数二分）

### [Sort](Sort/)

常见排序算法

### [string](String/)

字符串相关算法，kmp和马拉车

### [Tricks](Tricks/)

常见技巧，双指针等

### [Dynamic Programming](DynamicProgramming)

dp模型

---

### 从数据范围反推算法的技巧

一般ACM或者笔试题的时间限制是1秒或2秒。
在这种情况下，C++代码中的操作次数控制在 10<sup>7</sup>- 10<sup>8</sup> 为最佳。

下面给出在不同数据范围下，代码的时间复杂度和算法该如何选择：

- n≤30, 指数级别, dfs+剪枝，状态压缩dp
- n≤100 => O(n<sup>3</sup>)，floyd，dp，高斯消元
- n≤1000 => O(n<sup>2</sup>)，O(n<sup>2</sup>>logn)，dp，二分，朴素版Dijkstra、朴素版Prim、Bellman-Ford
- n≤10000 => O(n∗ sqrt(n))，块状链表、分块、莫队
- n≤100000 => O(nlogn) => 各种sort，线段树、树状数组、set/map、heap、拓扑排序、dijkstra+heap、prim+heap、spfa、求凸包、求半平面交、二分、CDQ分治、整体二
- n≤1000000 => O(n), 以及常数较小的O(nlogn)算法 => 单调队列、 hash、双指针扫描、并查集，kmp、AC自动机，常数比较小的 O(nlogn) 的做法：sort、树状数组、heap、dijkstra、spfa
- n≤10000000 =>O(n)，双指针扫描、kmp、AC自动机、线性筛素数
- n≤1e9=>O(n)，判断质数
- n≤1e18 =>O(logn)，最大公约数，快速幂
- n≤1e1000 =>O((logn)<sup>2</sup>)，高精度加减乘除
- n≤1e100000 => O(logk×loglogk)，k表示位数，高精度加减、FFT/NTT
