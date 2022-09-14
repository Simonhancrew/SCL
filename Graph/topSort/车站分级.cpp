#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/05/23

using namespace std;

/*
    每次车站从start->end,在这个形式的过程中假设停靠的站台集合是A，没有停靠的站台集合是B。
    一定有集合A >
   集合B。需要找到的结果是火车站级数最少，等价于求最小值，等价于差分约束的最长路
    最长路中，最后A > B，操作之前有A <
   B,需要连一条从B->A的边。因为最坏情况下，A和B集合的大小都是500
    会建立2500条边，这个结果最后是不能接受的，可以考虑的一个建边方法就是一个建立一个虚拟远点，描述两个集合的关系。
    B->FAKE = 0,FAKE->A = 1,最后的关系依然满足约束。
    随后做一次拓扑排序，之后拉满每一点的最短路就行。结果就取起点到终点的最大值（最长路）
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 2010,
          M = 1e6 + 10;  // 点多+m个，边每个最多500 + 500，一共1000次最多

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int st[N], d[N];
int q[N], dist[N];

void add(int a, int b, int c) {
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
  d[b]++;
}

void topsort() {
  int hh = 0, tt = -1;
  for (int i = 1; i <= n + m; i++) {
    if (!d[i]) q[++tt] = i;
  }
  while (hh <= tt) {
    int t = q[hh++];
    for (int i = h[t]; i != -1; i = ne[i]) {
      int j = e[i];
      if (--d[j] == 0) q[++tt] = j;
    }
  }
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m;
  memset(h, -1, sizeof h);
  for (int i = 1; i <= m; i++) {
    int cnt;
    cin >> cnt;
    int start = n, end = 1;
    memset(st, 0, sizeof st);
    while (cnt--) {
      int sta;
      cin >> sta;
      st[sta] = true;
      end = max(end, sta);
      start = min(start, sta);
    }

    int fake = n + i;  // 虚拟点，描述约束关系
    for (int j = start; j <= end; j++) {
      if (!st[j])
        add(j, fake, 0);
      else
        add(fake, j, 1);
    }
  }
  topsort();
  for (int i = 1; i <= n; i++) dist[i] = 1;
  for (int i = 0; i < n + m; i++) {
    int j = q[i];
    for (int k = h[j]; k != -1; k = ne[k]) {
      int t = e[k];
      dist[t] = max(dist[t], dist[j] + w[k]);
    }
  }
  int res = 0;
  for (int i = 1; i <= n; i++) res = max(res, dist[i]);
  cout << res << endl;
  return 0;
}