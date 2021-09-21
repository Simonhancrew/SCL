## 算法模板

Standar Code Library，2021/03/12开始学算法，记录算法的模板和算法学习。

由于算法知识点复杂，很多题其实是经验和技巧的结合，所以针对自己做过的题目做出一定的总结是必要的。

值得参考的repo就是[codeforces-go](https://github.com/EndlessCheng/codeforces-go)

### [bit](SCL/Bit/)

+ lowbit
+ 字节对齐
+ 二进制子集遍历

### [DataStruct](SCL/Datastruct/):

+ 单调栈 + 队列
+ Trie Tree
+ Union Find
+ heap
+ hash
+ todo:AC自动机，可持久化数据结构，平衡树，线段树，树状数组

### [Graph](SCL/Graph/)

+ BFS + DFS

+ Topsort

+ 最短路

+ 最小生成树

+ 二分图

### [greedyAlgo](SCL/greedyAlgorithm/)

+ 区间贪心

+ Huffman树

+ 不等式排序

+ 推公式

### [Math](SCL/Math/)

+ 质数
+ 约数
+ 欧拉
+ qmi
+ 高精度运算

### [random](SCL/Random/)

+ 随机处理

### [Search](SCL/Search/)

+ 整数二分和浮点数2分
+ todo:多源BFS，双向BFS，A*，双向DFS，IDA\*,Flood Fill.

### [Sort](SCL/Sort/)

常见排序算法

### [string](SCL/String/)

+ kmp
+ manacher

### [Tricks](SCL/Tricks/)

+ 双指针

### [Dynamic Programming](SCL/DynamicProgramming)

+ 背包模型
+ [线性dp]()
    + [数字三角模型]()
    + [最长上升子序列]()
    + 最长公共子序列
    
+ 区间dp模型
+ 计数dp
+ 状压dp
+ 树形dp
+ 记忆化搜索

## 周赛

基础的训练结束之后，周赛对我是比较有意义的，因为一般都会触及一两个弱势点。

目前我在刷完基础模板之后配合USACO Training的题目训练。

目前选择的赛事和每场的记录在competition下：

+ [leetcode周赛]()
+ [acwing周赛]()

周赛我关注的题目是两大类，

1. 第一，我会重点关注没做出来的题目，是算法不会还是技巧不会，还是单纯的逻辑错误。在事后着重进行补题
2. 第二，我可能会看前三选手的代码，这类竞赛选手一般代码实现都比较精美，复杂度很低，也是学习的对象


## 从数据范围反推算法的技巧

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
