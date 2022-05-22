## 拓扑排序

存在一个有向无环图的话，我们将图中的顶点以线性方式进行排序，使得对于任何的顶点u到v的有向边 , 都可以有u在v的前面.

## 实现算法

kahn算法，初始状态下，用一个队列维护所有的入度为0的点.

随后弹出一个队列中的点,对其连接的节点的入度做-1处理,如果某点的入度变为0,则入队.

直到集合为空,结束.

如果图中依然存在边,那么图一定是一个有环图.否则L就是一个拓扑序的结果.

```
bool toposort() {
    queue<int> q;
    for (i = 0; i < n; i++)
    if (in_deg[i] == 0) q.push(i);
    vector<int> ans;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        ans.push_back(u);
        for each edge(u, v) {
            if (--in_deg[v] == 0) q.push(v);
        }
    }
    if (ans.size() == n) {
        for (i = 0; i < n; i++)
            std::cout << ans[i] << std::endl;
        return true;
    } else {
        return false;
    }
}
```