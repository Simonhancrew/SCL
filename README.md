## Standar Code Library

> Standar Code Library，Begin At 2021/08/08.

---
Ranking points are meaningless, happiness is the essence

```
├── Bit
├── ComputationalGeometry
│   └── 凸包
├── Datastruct
│   ├── Automaton
│   ├── BalanceTree
│   │   └── RbTree
│   ├── Hash
│   ├── heap
│   ├── queue
│   ├── SegmentTree
│   ├── stack
│   │   └── 表达式求值
│   ├── TrieTree
│   ├── 单调栈
│   ├── 单调队列
│   ├── 可持久化数据结构
│   │   ├── 可持久化Trie
│   │   └── 可持久化线段树
│   ├── 平衡树
│   │   └── Treap
│   ├── 并查集
│   ├── 树状数组
│   ├── 跳表
│   └── 链表
├── DynamicProgramming
│   ├── RMQ
│   ├── 区间dp
│   ├── 单调队列优化dp
│   ├── 数位统计dp
│   ├── 树形dp
│   ├── 状态压缩dp
│   ├── 状态机模型
│   ├── 线性dp
│   │   ├── 数字三角形模型
│   │   └── 最长上升子序列模型
│   ├── 背包问题
│   ├── 计数类dp
│   └── 记忆化搜索
├── Graph
│   ├── Astar
│   ├── BFS
│   │   ├── FloodFill
│   │   ├── 双向BFS
│   │   ├── 双端队列广搜
│   │   ├── 多源BFS
│   │   ├── 最小步数模型
│   │   └── 边权恒定最短路
│   ├── DFS
│   │   ├── 剪枝方式
│   │   ├── 双向DFS
│   │   ├── 回溯
│   │   ├── 子节点计数
│   │   ├── 搜索顺序
│   │   ├── 连通性问题
│   │   └── 迭代加深
│   ├── EulerPath
│   ├── IDAstar
│   ├── LCA
│   ├── topSort
│   ├── 二分图
│   │   ├── 匈牙利算法
│   │   └── 染色法判断二分图
│   ├── 单源最短路问题
│   │   ├── 单源最短路扩展
│   │   ├── 单源最短路的建图
│   │   └── 最短路综合应用
│   ├── 图的宽搜
│   ├── 差分约束
│   ├── 无向图的双连通分量
│   ├── 最小生成树
│   │   ├── Kruskal
│   │   └── Prim
│   ├── 最短路
│   │   ├── bellmanFord
│   │   ├── Dijkstra
│   │   ├── Floyd
│   │   └── spfa
│   ├── 有向图的强连通分量
│   ├── 树的深搜
│   └── 负环
├── greedyAlgorithm
│   ├── Huffman树
│   ├── 区间贪心问题
│   ├── 排序不等式
│   ├── 推公式
│   ├── 最短距离类问题
│   └── 绝对值不等式
├── Log
├── Math
│   ├── 01分数规划
│   ├── Congruence
│   │   └── 扩展欧几里得算法
│   ├── Euler
│   ├── Matrix
│   ├── presum
│   ├── 中国剩余定理
│   ├── 乱七八糟的定理
│   ├── 众数
│   ├── 容斥原理
│   ├── 差分
│   ├── 快速幂
│   ├── 矩阵乘法
│   ├── 离散化
│   ├── 简单博弈论
│   ├── 约数
│   ├── 组合数
│   ├── 质数
│   ├── 高斯消元
│   └── 高精度运算
├── Random
├── Search
│   ├── BinarySearch
│   └── FloatBinarySearch
├── Sort
│   ├── BubbleSort
│   ├── DoubleDirectionBubbleSort
│   ├── MergeSort
│   ├── QuickSelect
│   └── Quicksort
├── String
│   └── KMP
├── Transform
└── Tricks
    ├── 区间合并
    ├── 双指针
    └── 递推和递归
```

## 数据范围

一般C++的复杂度控制在10^7左右是比较稳的，前提是数据范围不卡常

1. n ≤ 30 => 指数级别
    > dfs+剪枝，状态压缩dp
2. n ≤ 100 => O($n^3$)
    > floyd，dp，高斯消元
3. n ≤ 1000 => O($n^2$)或者O($n^2 \times \log_{2}{n}$)
    > dp，二分，朴素版Dijkstra、朴素版Prim、Bellman-Ford
4. n ≤ $10^4$ => O($n \times \sqrt{n}$)或者O(n)
    > 块状链表、分块、莫队
5. n ≤ $10^5$ => O($n \times \log_{2}{n}$)
    > 各种sort，线段树、树状数组、set/map、heap、拓扑排序、dijkstra+heap、prim+heap、Kruskal、spfa、求凸包、求半平面交、二分、CDQ分治、整体二分、后缀数组、树链剖分、动态树
6. n ≤ $10^6$ => O(n), 以及常数较小的 O($n \times \log_{2}{n}$)
    > 单调队列、 hash、双指针扫描、并查集，kmp、AC自动机，常数比较小的O($nlogn$)的做法：sort、树状数组、heap、dijkstra、spfa
7. n ≤ $10^7$ => O(n)
    > 双指针扫描、kmp、AC自动机、线性筛素数
8. n≤ $10^9$ => O($n \times \sqrt{n}$)，
    > 判断质数
9. n ≤ $10^{18}$ => O($\log_{2}{n}$)
    > 最大公约数，快速幂，数位DP
10. n ≤ $10^{1000}$ => O($(log_{2}{n})^2$)，
    > 高精度加减乘除
11. n ≤ $10^{100000}$ => O($\log{k} \times \log{\log{k}}$)，k表示位数，
    > 高精度加减, `FFT/NTT`

## Reference

+ [codeforces-go](https://github.com/EndlessCheng/codeforces-go)
+ [OI-Wiki](https://oi-wiki.org/)

