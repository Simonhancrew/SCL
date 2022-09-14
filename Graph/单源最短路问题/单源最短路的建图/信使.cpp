#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

// Created by Simonhancrew on 2022/03/23

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 110, M = 200 * 2 + 10;

struct edge {
  int v, w;
};

#define BELLMANFORD 1
#define SPFA 0
#define FLOYD 0
#define DIJ 0
#define DJIHEAP 0

int n, m;
int g[N][N];
#if DIJ
int e[M], ne[M], w[M], h[N], idx;
#endif
int st[N], d[N];
#if BELLMANFORD
vector<edge> e[N];
#endif
#if DIJ
void add(int a, int b, int c) {
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
#endif

#if BELLMANFORD
bool bellmanford() {
  d[1] = 0;
  bool flag = false;
  for (int i = 0; i < n; i++) {
    flag = false;
    for (int u = 1; u <= n; u++) {
      if (d[u] == INF) continue;
      for (auto ed : e[u]) {
        int v = ed.v, w = ed.w;
        if (d[v] > d[u] + w) {
          d[v] = d[u] + w;
          flag = true;
        }
      }
    }
    if (!flag) break;
  }
  return flag;
}
#endif

#if SPFA
void spfa() {
  d[1] = 0, st[1] = 1;
  queue<int> q;
  q.push(1);
  while (q.size()) {
    auto t = q.front();
    q.pop();
    st[t] = 0;
    for (int i = h[t]; i != -1; i = ne[i]) {
      int j = e[i];
      if (d[j] > d[t] + w[i]) {
        d[j] = d[t] + w[i];
        if (st[j]) continue;
        st[j] = true;
        q.push(j);
      }
    }
  }
}
#endif

#if DIJ
void dijstra() {
  d[1] = 0;
  for (int i = 0; i < n; i++) {
    int t = -1;
    for (int j = 1; j <= n; j++) {
      if (!st[j] && (t == -1 || d[t] > d[j])) {
        t = j;
      }
    }
    st[t] = true;
    for (int j = 1; j <= n; j++) {
      d[j] = min(d[j], d[t] + g[t][j]);
    }
  }
}
#endif

#if DIJHEAP
void dijstra() {
  priority_queue<PII, vector<PII>, greater<PII>> heap;
  heap.push({0, 1});
  d[1] = 0;
  while (heap.size()) {
    auto t = heap.top();
    heap.pop();
    int node = t.second, dist = t.first;
    if (st[node]) continue;
    st[node] = true;
    for (int i = h[node]; i != -1; i = ne[i]) {
      int j = e[i];
      if (d[j] > dist + w[i]) {
        d[j] = dist + w[i];
        heap.push({d[j], j});
      }
    }
  }
}
#endif

int main() {
  fast_cin();
  cin >> n >> m;
#if FLOYD
  memset(g, 0x3f, sizeof g);
  for (int i = 1; i <= n; i++) g[i][i] = 0;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a][b] = g[b][a] = min(g[a][b], c);
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
#endif
#if SPFA
  memset(d, 0x3f, sizeof d);
  memset(h, -1, sizeof h);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    add(a, b, c), add(b, a, c);
  }
  spfa();
#endif
#if BELLMANFORD
  memset(d, 0x3f, sizeof d);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    e[a].push_back({b, c});
    e[b].push_back({a, c});
  }
  bellmanford();

#endif
#if DIJ
  memset(d, 0x3f, sizeof d);
  memset(g, 0x3f, sizeof g);
  for (int i = 1; i <= n; i++) g[i][i] = 0;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a][b] = min(g[a][b], c);
    g[b][a] = min(g[b][a], c);
  }
  dijstra();
#endif
#if DJIHEAP
  memset(d, 0x3f, sizeof d);
  memset(h, -1, sizeof h);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    add(a, b, c), add(b, a, c);
  }

  dijstra();
#endif
  int res = -1;
  for (int i = 1; i <= n; i++) {
    if (d[i] == INF) {
      res = -1;
      break;
    }
    res = max(res, d[i]);
  }
  cout << res << endl;
  return 0;
}