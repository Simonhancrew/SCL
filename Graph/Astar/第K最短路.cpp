#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

/*
    A*的：
        估计距离<=真实距离
        针对点u,入队的估计和为 d[u] + f[u]
        其中d[u]是起点到u的真实距离，f[u]是u到终点的估价距离，其中f[u] <=
   g[u],g[u]是u 到终点的真实距离 则必然有f[u] + d[u] <= d[u] + g[u]
        因此，出队的时候假设dist > d(best) >= d[u] +
   f[u]，使用的是小根堆，相矛盾了，对立有比出队 的时候更小的估价和

        除了终点之外，所有点出队的时候的距离都不一定能真实反应当前点的最后距离
        例如一个例子
        A       。。。。。
                。      。
                。      。
        start   。。。。。。。。。。。。。。。。。。。。。end
                    B                        C
        假设B的估价距离f[B] =
   g[B]取到真实值(很大)，A的估价距离取0（全部的估价距离取0的时候可以看作一个DIJ），
        每个点的真实边权取1，这个时候是会先更新start -> A ->
   C这一条路的（假设到C的时候估价距离和大于了B），
        每个点到终点的估价距离不一定是真实反映值.

    这里可以用Dij做一次从终点到起点的最短路更新，然后用dist最为A*中的估价值
*/

#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)

typedef pair<int, int> PII;
typedef pair<int, PII> PIII;

#define x first
#define y second

const int N = 1e3 + 10, M = 2e5 + 10, INF = 0x3f3f3f3f;

int n, m;
int h[N], rh[N], e[M], ne[M], w[M], idx;
int dist[N];
bool st[N];
int S, T, K;
int cnt[N];

void add(int h[], int a, int b, int c) {
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

// 启发函数这里用当前点到终点的真实距离就可以了
// 反向做一次Dij就行
void dijstra() {
  memset(dist, 0x3f, sizeof dist);
  priority_queue<PII, vector<PII>, greater<PII>> heap;
  heap.push({0, T});
  dist[T] = 0;
  while (heap.size()) {
    auto t = heap.top();
    heap.pop();
    int node = t.y;
    if (st[t.y]) continue;
    st[t.y] = true;
    for (int i = rh[node]; i != -1; i = ne[i]) {
      int j = e[i];
      if (dist[j] > dist[node] + w[i]) {
        dist[j] = dist[node] + w[i];
        heap.push({dist[j], j});
      }
    }
  }
}

int astar() {
  if (dist[S] == INF) return -1;  // 保证有解
  priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
  heap.push({dist[S], {0, S}});
  while (heap.size()) {
    auto t = heap.top();
    heap.pop();
    int node = t.y.y, d = t.y.x;
    cnt[node]++;
    if (cnt[T] == K) return d;
    // A*在这里不根据距离更优做更新与否，因为最终是要搜到第K短路的
    for (int i = h[node]; i != -1; i = ne[i]) {
      int j = e[i];
      // j已经入对K次了，但是终点依然没有到达K次，再继续更新j是没有意义的
      // 题目无解的时候做这个判断是有必要的否则可以无限入队
      if (cnt[j] < K) heap.push({d + w[i] + dist[j], {d + w[i], j}});
    }
  }
  return -1;
}

int main() {
  fast_cin();
  cin >> n >> m;
  memset(h, -1, sizeof h);
  memset(rh, -1, sizeof rh);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    add(h, a, b, c);
    add(rh, b, a, c);
  }
  cin >> S >> T >> K;
  dijstra();
  if (S == T) K++;
  cout << astar() << endl;
  return 0;
}