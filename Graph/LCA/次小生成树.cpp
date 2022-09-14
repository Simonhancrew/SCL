#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/05/19

using namespace std;

/*
    次小生成树的的求法：先kruskal求最小生成树，随后将非树边加入，并在形成的环上
    移除一个最大值，如果最大值和加入的非树边相等则移除次大值。
    这个求解最大值的树边可以用lca来做，d1[i][j]是从i开始往上跳2^j步的所走过的边中的最大值，d2是次大值
    最后遍历非树边求解一次结果
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10, M = 3e5 + 10;

struct Edge {
  int a, b, w;
  bool used;
} edge[M];

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int p[N], depth[N], q[N];
int fa[N][17], d1[N][17], d2[N][17];

void add(int a, int b, int c) {
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int find(int x) {
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}

LL kruskal() {
  LL res = 0;
  for (int i = 1; i <= n; i++) p[i] = i;
  sort(edge, edge + m, [](Edge &l, Edge &r) { return l.w < r.w; });
  for (int i = 0; i < m; i++) {
    int a = find(edge[i].a), b = find(edge[i].b), w = edge[i].w;
    if (a != b) {
      p[a] = b;
      res += w;
      edge[i].used = true;
    }
  }
  return res;
}

void build() {
  memset(h, -1, sizeof h);
  for (int i = 0; i < m; i++) {
    if (edge[i].used) {
      int a = edge[i].a, b = edge[i].b, w = edge[i].w;
      add(a, b, w), add(b, a, w);
    }
  }
}

void bfs() {
  memset(depth, 0x3f, sizeof depth);
  int hh = 0, tt = 0;
  depth[0] = 0, depth[1] = 1;
  q[0] = 1;
  while (hh <= tt) {
    int t = q[hh++];
    for (int i = h[t]; i != -1; i = ne[i]) {
      int j = e[i];
      if (depth[j] > depth[t] + 1) {
        depth[j] = depth[t] + 1;
        q[++tt] = j;

        fa[j][0] = t;
        d1[j][0] = w[i], d2[j][0] = -INF;
        for (int k = 1; k <= 16; k++) {
          int anc = fa[j][k - 1];
          fa[j][k] = fa[anc][k - 1];
          int dist[4] = {d1[j][k - 1], d2[j][k - 1], d1[anc][k - 1],
                         d2[anc][k - 1]};
          d1[j][k] = d2[j][k] = -INF;
          for (int u = 0; u < 4; u++) {
            int d = dist[u];
            if (d > d1[j][k])
              d2[j][k] = d1[j][k], d1[j][k] = d;
            else if (d < d1[j][k] && d > d2[j][k])
              d2[j][k] = d;
          }
        }
      }
    }
  }
}

int lca(int a, int b, int w) {
  if (depth[a] < depth[b]) swap(a, b);
  static int dist[N * 2];
  int cnt = 0;
  for (int i = 16; i >= 0; i--) {
    if (depth[fa[a][i]] >= depth[b]) {
      dist[cnt++] = d1[a][i];
      dist[cnt++] = d2[a][i];
      a = fa[a][i];
    }
  }
  if (a != b) {
    for (int i = 16; i >= 0; i--) {
      if (fa[a][i] != fa[b][i]) {
        dist[cnt++] = d1[a][i];
        dist[cnt++] = d2[a][i];
        dist[cnt++] = d1[b][i];
        dist[cnt++] = d2[b][i];
        a = fa[a][i], b = fa[b][i];
      }
    }
    dist[cnt++] = d1[a][0], dist[cnt++] = d1[b][0];
  }
  int dist1 = -INF, dist2 = -INF;
  for (int i = 0; i < cnt; i++) {
    int d = dist[i];
    if (d > dist1)
      dist2 = dist1, dist1 = d;
    else if (d < dist1 && d > dist2)
      dist2 = d;
  }
  if (w > dist1) return w - dist1;
  if (w > dist2) return w - dist2;
  return INF;
}

int main() {
  fast_cin();
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> edge[i].a >> edge[i].b >> edge[i].w;
  }
  LL sum = kruskal();
  build();
  bfs();

  LL res = 1e18;
  for (int i = 0; i < m; i++) {
    if (!edge[i].used) {
      int a = edge[i].a, b = edge[i].b, w = edge[i].w;
      res = min(res, sum + lca(a, b, w));
    }
  }
  cout << res << endl;
  return 0;
}