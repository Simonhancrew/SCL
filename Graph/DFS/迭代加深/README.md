## 迭代加深

迭代加深是一种 每次限制搜索深度的深度优先搜索。

它的本质还是深度优先搜索，只不过在搜索的同时带上了一个深度 ，当d达到设定的深度时就返回，一般用于找最优解。如果一次搜索没有找到合法的解，就让设定的深度加一，重新从根开始。

### 关于为什么不用BFS

BFS过程中不可避免的用到一个队列维护整体的状态，当队列的状态很多，或者单个状态非常大的时候，BFS就具有一定的劣势。迭代加深DFS就很类似用DFS的方式实现BFS（空间复杂度相对较小）。

搜索树的分支很大的时候，每增加一层搜索的空间，搜索的复杂度会指数级别增长，这个时候针对前面部分的重复搜索带来的复杂度其实是很小的。

### 步骤

首先设定一个较小的深度作为全局变量`d`，进行DFS。每进入一次DFS，将当前深度加一，当发现`d`大于设定的深度`limit`就返回。如果在搜索的途中发现了答案就可以回溯，同时在回溯的过程中可以记录路径。如果没有发现答案，就返回到函数入口，增加设定深度，继续搜索。

```
IDDFS(u,d)
    if d>limit
        return
    else
        for each edge (u,v)
            IDDFS(v,d+1)
  return
```

### 注意事项

在大多数的题目中，广度优先搜索还是比较方便的，而且容易判重。当发现广度优先搜索在空间上不够优秀，而且要找最优解的问题时，就应该考虑迭代加深。

> [参考:OI-WIKI](https://oi-wiki.org/search/iterative/)