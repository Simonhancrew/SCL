#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

// Created by Simonhancrew on 2022/03/22

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 2510, M = 6200 * 2 + 10;

int n, m, S, T;
int e[M], ne[M], h[N], w[M], idx;
int dist[N], st[N];
int g[N][N];

#define SPFA 0
#define DIJ 0
#define HEAPDIJ 1

void add(int a, int b, int c) {
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void spfa() {
  dist[S] = 0;
  queue<int> q;
  q.push(S);
  st[S] = 1;
  while (q.size()) {
    int t = q.front();
    q.pop();
    st[t] = 0;
    for (int i = h[t]; i != -1; i = ne[i]) {
      int j = e[i];
      if (dist[j] > dist[t] + w[i]) {
        dist[j] = dist[t] + w[i];
        if (!st[j]) {
          q.push(j);
          st[j] = true;
        }
      }
    }
  }
}

void dijstra() {
  dist[S] = 0;
  for (int i = 0; i < n - 1; i++) {
    int t = -1;
    for (int j = 1; j <= n; j++) {
      if (!st[j] && (t == -1 || dist[j] < dist[t])) {
        t = j;
      }
    }
    st[t] = 1;
    for (int j = 1; j <= n; j++) {
      dist[j] = min(dist[j], dist[t] + g[t][j]);
    }
  }
}

void dijstra(int unuse) {
  priority_queue<PII, vector<PII>, greater<PII>> heap;
  dist[S] = 0;
  heap.push({0, S});
  while (heap.size()) {
    auto t = heap.top();
    heap.pop();
    int node = t.second, d = t.first;
    if (st[node]) continue;
    st[node] = true;
    for (int i = h[node]; i != -1; i = ne[i]) {
      int j = e[i];
      if (dist[j] > dist[node] + w[i]) {
        dist[j] = dist[node] + w[i];
        heap.push({dist[j], j});
      }
    }
  }
}

int main() {
  fast_cin();
  memset(h, -1, sizeof h);
  memset(dist, 0x3f, sizeof dist);
  memset(g, 0x3f, sizeof g);
  cin >> n >> m >> S >> T;
#if SPFA
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    add(a, b, c), add(b, a, c);
  }
  spfa();
#endif
#if DIJ
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a][b] = c, g[b][a] = c;
  }
  dijstra();
#endif
#if HEAPDIJ
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    add(a, b, c), add(b, a, c);
  }
  dijstra(0);
#endif
  cout << dist[T] << endl;
  return 0;
}