## 强连通分量

强连通的定义： 有向图G中，G中任意两个节点连通。

强连通分量： 极大的强连通子图

有向图可以通过缩点的方式(强连通分量缩成一个点)，变成一个DAG

### 应用

求最短路和最长路，递推

### 实现算法(tarjan)

首先明确几个定义(虽然不太重要):

1. 树枝边: 每次搜索到还没访问节点的时候就形成了一个树边

2. 前向边：特殊的树边，搜索的时候遇到子树中的节点的时候形成

3. 后向边： 指向祖先节点的边

4. 横向边： 搜索的时候遇到了一个访问过的节点，但是并不是祖先

具体的tarjan中需要维护几个变量：

0. timestamp,一个时间片，维护搜索节点的发现时间

1. dfn[u],深度优先遍历时u被搜的时间序

2. low[u],能回溯到的已经在栈中最早的点。假设以u为根的子树tr[u],low[u]是其可达节点dfn[u]的最小值=>tr[u]子节点的dfn[x]最小值，从tr[u]通过不在搜索树上的边能到达的点)

在深度优先搜索中，考虑节点u和其子节点v的相关情况，主要有以下的几个关系：

1. v没有被访问过：继续对v进行深度优先搜索。在回溯过程中，用low[v]去更新low[u],因为存在从u->v的路径，所以v能回溯到的在栈中的节点，u也一定能回溯到

2. v被访问过，在栈中，根据low值的定义，用dfb[v]更新low[u].

3. v被访问过，不在栈中，说明此时的v已经搜索完毕了，其强连通分量被完全处理。不用做额外的操作

其伪代码实现如下：
```
TARJAN_SEARCH(int u)
    vis[u]=true
    low[u]=dfn[u]=++dfncnt
    push u to the stack
    for each (u,v) then do
        if v hasn't been searched then
            TARJAN_SEARCH(v) // 搜索
            low[u]=min(low[u],low[v]) // 回溯
        else if v has been in the stack then
            low[u]=min(low[u],dfn[v])
```

比较容易想到，在连通图中，仅有一个u使得low[u] = dfn[u],该节点一定是深度遍历中，该连通分量第一个被访问过的节点，因为他的dfn[u]和low[u]都最小，不会被该连通分量中的其余分量所影响。

在回溯过程中，判定dfn[u] == low[u]是否成立，成立的话则栈u和其上方的点构成一个SCC(Strong connected Component)

```cpp
// C++ Version
int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
int scc[N], sc;  // 结点 i 所在 SCC 的编号
int sz[N];       // 强连通 i 的大小

void tarjan(int u) {
  low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
  for (int i = h[u]; i; i = e[i].nex) {
    const int &v = e[i].t;
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (in_stack[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++sc;
    while (s[tp] != u) {
      scc[s[tp]] = sc;
      sz[sc]++;
      in_stack[s[tp]] = 0;
      --tp;
    }
    scc[s[tp]] = sc;
    sz[sc]++;
    in_stack[s[tp]] = 0;
    --tp;
  }
}
```