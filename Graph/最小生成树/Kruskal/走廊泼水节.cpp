#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/05/01

using namespace std;

/*
    完全图，节点间完全相连，等价于不同集合合并中，每个集合点互连
    求树的唯一一个生成图，做kruskal的时候不同集合每对点间加边w + 1就行了。
    因此并查集需要额外维护每个集合的节点数量
    证明唯一，按照边权顺序做，假设还有另一种最小生成树的方案，因为原图[i,j]是确定最小的
    如果还有另一种方案的话，[i,j]替换路径中的一条边，一定获得更小的结果
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 6010;

int n;
int p[N], sz[N];

struct edge {
  int u, v, w;
} e[N];

int find(int x) {
  if (p[x] != x) {
    p[x] = find(p[x]);
  }
  return p[x];
}

int main() {
  fast_cin();
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      e[i] = {u, v, w};
    }
    for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;

    sort(e, e + n - 1, [](edge &l, edge &r) { return l.w < r.w; });

    int res = 0;
    for (int i = 0; i < n - 1; i++) {
      int u = find(e[i].u), v = find(e[i].v);
      int w = e[i].w;

      if (u != v) {
        res += (sz[u] * sz[v] - 1) * (w + 1);
        p[u] = v;
        sz[v] += sz[u];
      }
    }

    cout << res << endl;
  }
  return 0;
}