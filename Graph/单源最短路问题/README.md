## 单源最短路

若一张图的边数远小于其点数的平方，则这是一张稀疏图

若一张图的边数接近其点数的平方，则这是一张稠密图

单源最短路的图有几个解法，具体需要根据建图之后的复杂度做具体的判断

### 加边操作

实际就是数组模拟的头插拉链法

```cpp
int h[N],e[N],ne[N],w[N],idx;

void add(int a,int b,int c)
{
    // w[i]，当前b到a的距离
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
```

### Floyd

floyd主要用来求任意一点之间的最短路的，复杂度很高，但是常数很小。适用于任何图（也就是无论是否有向，是否带负权），但要求不带负权回路，至少存在一个最短路。直接二维数组记录距离就可以了

复杂度是$O(n^3)$的

```cpp
void floyd(){
    for(int k = 1;k <= n;k++){
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
            }
        }
    }
}
```

### Bellmanford

bellmanford的思路比较简单，主要涉及一个松弛操作。可以求出有负权的图的最短路，并可以对最短路不存在的情况进行判断。

主要针对边做最短路的求解，$dis(v) =min(dis(v),dis(u) + w(u,v))$,针对每一条边，尝试松弛。在某一轮循环中，完全没有松弛操作的时候就停止操作。因此记录所有的边就可以了

假设点n，边m。遍历所有的边需要$O(m)$的复杂度

最坏情况下，每一次松弛操作会让最短路的边数至少+1，最短路的边数最多是n-1.

总的时间复杂度会是$O(mn)$

```cpp
int bellman_ford(){
    memset(dist,0x3f,sizeof dist);
    dist[1] = 0;
    
    for(int i = 0;i < k;i++){
        //备份数组，防止串联，每一次都用上次更新的去做更更新。
        //不用本次更新过的点去做更新
        memcpy(backup,dist,sizeof dist);
        for(int j = 0;j < m;j++){
            int a = edge[j].a,b = edge[j].b,w = edge[j].w;
            dist[b] = min(dist[b],backup[a] + w);
        }
    }
    //可能存在负权边，找一个很大的数  
    if(dist[n] > 0x3f3f3f3f / 2) return -1;
    return dist[n];
}
```
### Spfa

spfa更像是bellmanford的队列优化，实质上不需要那么多的松弛操作，只需要松弛上一轮松弛的点就可以了。只有上一次松弛过的点可能造成后续的松弛。

用一个队列来维护哪些点是可能造成松弛操作的，只访问必要的边

不幸的是，最复杂情况下，spfa的复杂度依然是$O(mn)$的

```cpp
int spfa(){
    // 1 所有距离置0x3f,起点置零
    memset(d,0x3f,sizeof d);
    d[1] = 0;
    // 2 将更新了的最短距离放进队列中,重复的放没有错，但是效率会下降
    queue<int> q;
    q.push(1);
    st[1] = true; // 这里为了防止节点重复放入
    // 3 利用队列中的节点更新周围节点
    while(q.size()){
        int t = q.front();
        q.pop();
        st[t] = false;
        // 周围节点
        for(int i = h[t];i != -1;i = ne[i]){
            int j = e[i];
            // 确定距离是否变小了
            if(d[j] > d[t] + w[i]){
                d[j] = d[t] + w[i];
                // 确定在不在集合里，在集合里的都是变小了的，没必要重复加入
                if(!st[j]) q.push(j),st[j] = true;
            }
        }
    }
    if(d[n] == 0x3f3f3f3f) return -1;
    return d[n];
}
```

### Dijstra

求解**非负权图**的利器，有多种数据结构优化的方式。

记住将整体集合分成两部分，已经确定了最短路的集合$S$和未确定最短路的集合$T$。

初始，起点是s，`dis[s] = 0`,其余距离均为正无穷。此时是都没确定最短路的

重复下述操作：

1. 从T中选取一个最短路最小的节点，移到集合S中。

2. 对刚刚加入集合的节点的出边做一个松弛操作。

集合T空了的时候，整体的操作结束。

不用任何数据结构优化的情况下，在松弛操作之后暴力寻找最小节点，整体的复杂度是$O(n^2)$,松弛操作的复杂度是O(m),整体的复杂度就是$O(n^2 + m)$
,需要根据稠密图和稀疏图具体判断，稠密图用就还能接受。复杂度

```cpp
// 朴素dijkstra求最短路
int dijsktra(){
    // 1 初始的时候距离都为无穷大，起点距离为0
    memset(d,0x3f,sizeof d);
    d[1] = 0,st[1] = 0;
    // 2 遍历n次，找到起点到每个点的最小距离
    for(int i = 0;i < n - 1;i++){
        int t = -1;
        // 3 找到未确定最短距离，且距离起点值最小的点
        for(int j = 1;j <= n;j++){
            if(!st[j] && (t == -1 || d[t] > d[j])){
                t = j;
            }
        }
        // 4 之后这个点到起点的最小距离就确定了，加入集合st
        st[t] = 1;
        // 5 然后用这个确定了最小距离的点，更新一下周围的距离（注意，这些点的距离还是未确定最小的）
        for(int j = 1;j <= n;j++){
            d[j] = min(d[j],d[t] + g[t][j]);
        }
    }
    // 6 如果此时的距离还是无穷大，说明根本就不可能到达.否则就是一个可行解
    if(d[n] == 0x3f3f3f3f) return -1;
    return d[n];
}
```

### 堆优化Dijstra

用优先队列优化找寻最小距离的过程，因为不能删，共计m次插入，故队列中的空间是O(m)的，总体的时间复杂度$O(mlogm)$。稀疏图用就很不错

```cpp
// 堆优化dijkstra
int dijkstra(){
    // 1 初始距离
    memset(d,0x3f,sizeof d);
    d[1] = 0;
    // 2 利用最小堆来找不在确定集合中的最小距离
    priority_queue<PII,vector<PII>,greater<PII>> heap;
    heap.push({0,1});
    while(heap.size()){
        auto t = heap.top();
        heap.pop();
        int node = t.second,dis = t.first;
        // 2 按照第一个元素排序，可能存在冗余，直接判断就好
        if(st[node]) continue;
        // 3 将这个最小的距离加入确定集合
        st[node] = true;
        // 4 利用这个距离来更新他周围的点到起点的距离
        for(int i = h[node];i != -1;i = ne[i]){
            int j = e[i];
            if(d[j] > d[node] + w[i]){
                d[j] = d[node] + w[i];
                heap.push({d[j],j});
            }
        }
    }
    // 5 判断
    if(d[n] == 0x3f3f3f3f) return -1;
    return d[n];
}
```