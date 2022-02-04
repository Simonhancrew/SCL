## A*

BFS的优化，一种求最短路的算法，需要一个估价函数（启发函数），只需要遍历很少的路径就能够搜到结局

点数非常庞大的时候A*算法会有很大的优势

```
    A*的：
        估计距离<=真实距离
        针对点u,入队的估计和为 d[u] + f[u]
        其中d[u]是起点到u的真实距离，f[u]是u到终点的估价距离，其中f[u] <= g[u],g[u]是u
        到终点的真实距离
        则必然有f[u] + d[u] <= d[u] + g[u]
        因此，出队的时候假设dist > d(best) >= d[u] + f[u]，使用的是小根堆，相矛盾了，对立有比出队
        的时候更小的估价和

        除了终点之外，所有点出队的时候的距离都不一定能真实反应当前点的最后距离
        例如一个例子
        A       。。。。。
                。      。
                。      。
        start   。。。。。。。。。。。。。。。。。。。。。end
                    B                        C
        假设B的估价距离f[B] = g[B]取到真实值(很大)，A的估价距离取0（全部的估价距离取0的时候可以看作一个DIJ），
        每个点的真实边权取1，这个时候是会先更新start -> A -> C这一条路的（假设到C的时候估价距离和大于了B），
        每个点到终点的估价距离不一定是真实反映值. 
```

BFS中的队列会被换成优先队列，除了存储真实距离（起点到当前点）之外还要存储估价距离（从当前点到终点的猜测距离），排序的是整个估价 + 真实

A*的思路往往比较简单，但是代码的实现往往稍复杂

```
// 一个启发函数，用来估价 
int f(string state) {

}

while(heap.size()) { // 小根堆
    auto t = heap.top();
    heap.pop();
    if t == end:
        \\终点第一次出队的时候：
        break
    for(t : nei[t]) {
        判断合法性
        临边入队(dist[t] + f(t))
    }
}
```