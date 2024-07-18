# dijkstra

在全是正权变的图中，求出起点到所有点的最短路

## 算法步骤

1. 首先从已经预备有距离的点中找到距离起点最近的点，这个点的最小距离就被确认了

2. 然后更新与这个点相邻的点的距离, 预备距离的点集就被更新了。然后重复第一步，直到所有点的最小距离都被确认

假设的原则在于，用反证法，如果在第一步中存在一个点u，经过u到达v的距离比从起点x到达v的距离更短

说明起点到u的距离一定是更小的，这与我们的假设矛盾

```cpp
vector<int> dis(n, INT_MAX);
dis[0] = 0;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
pq.emplace(0, 0);
while (!pq.empty()) {
    auto [dx, x] = pq.top();
    pq.pop();
    if (dx > dis[x]) { // x 之前出堆过
        continue;
    }
    for (auto &[y, d] : g[x]) {
        int new_dis = dx + d;
        if (new_dis < dis[y]) {
            dis[y] = new_dis; // 更新 x 的邻居的最短路
            pq.emplace(new_dis, y);
        }
    }
}
```
