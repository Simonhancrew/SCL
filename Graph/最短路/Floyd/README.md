## FLOYD

可用于求任意两点之间的最短路，代码很容易实现。复杂度很高，但是常数很小。

适用于任何图，无论边是否有向，边权正负(前提是最短路必须存在)

### 实现

可以参考0x3f的[这篇题解](https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/solutions/2525946/dai-ni-fa-ming-floyd-suan-fa-cong-ji-yi-m8s51/?envType=daily-question&envId=2023-11-14), 从dfs出发一步步到递推。

原理参考dp，f[k][x][y]代表只允许经过[1,k]节点(值得注意的是，此时整体路径是[1,k]的，但是x和y不一定在这个图中)，节点x到y的最短路长度。

显然可以知道f[n][x][y]就是节点x到y的最短长度。

f[0][x][y],其值应该是x->y的边权(或者是INF or 0)

1. 初始的时候不确定有没有直接边，应全部赋值为INF

2. x和y是同一个点的时候，0

3. 当存在x<->y的边的时候，应该赋值为边权

f[k][x][y] = min(f[k-1][x][y], f[k-1][x][k]+f[k-1][k][y])

这也很好理解，f[k - 1][x][y]是不经过k的x->y的最短路，右边的f[k-1][x][k] + f[k - 1][k][y]是经过了k点的最短路

所以不难有一个代码
```
for (k = 1; k <= n; k++) {
  for (x = 1; x <= n; x++) {
    for (y = 1; y <= n; y++) {
      f[k][x][y] = min(f[k - 1][x][y], f[k - 1][x][k] + f[k - 1][k][y]);
    }
  }
}
```
第一维的数组可以省略，去掉第一维k之后等价变成
```
f[x][y] = min(f[x][y],f[x][k] + f[k][y])
```
实质上，后一部分的f[x][k] + f[k][y]是来自上一层的计算结果，循环最外层的k是递增执行的。
所以等价变化之后等式的含义不变，依然是` min(f[k - 1][x][y], f[k - 1][x][k] + f[k - 1][k][y])`，原位修改是可以的。

```cpp
for (k = 1; k <= n; k++) {
  for (x = 1; x <= n; x++) {
    for (y = 1; y <= n; y++) {
      f[x][y] = min(f[x][y], f[x][k] + f[k][y]);
    }
  }
}
```

### 应用

1. 最短路

2. 传递闭包

3. 求最小环

