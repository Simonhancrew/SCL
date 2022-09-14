#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

// Created by Simonhancrew on 2022/04/14

using namespace std;

/*
    有环和重边，类似于dp求方案数
    关键在于最短路中不一定存在拓扑序，
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, P = 1e5 + 3, N = 1e5 + 10, M = 4e5 + 10;

int n, m;
int h[N], e[M], ne[M], idx;
int dist[N], cnt[N];

void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

void bfs() {
  memset(dist, 0x3f, sizeof dist);
  dist[1] = 0;
  cnt[1] = 1;
  queue<int> q;
  q.push(1);
  while (q.size()) {
    auto t = q.front();
    q.pop();
    for (int i = h[t]; i != -1; i = ne[i]) {
      int j = e[i];
      if (dist[j] > dist[t] + 1) {
        dist[j] = dist[t] + 1;
        cnt[j] = cnt[t];
        q.push(j);
      } else if (dist[j] == dist[t] + 1) {
        cnt[j] = (cnt[j] + cnt[t]) % P;
      }
    }
  }
}

int main() {
  fast_cin();
  cin >> n >> m;
  memset(h, -1, sizeof h);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    add(x, y), add(y, x);
  }
  bfs();
  for (int i = 1; i <= n; i++) cout << cnt[i] << endl;
  return 0;
}