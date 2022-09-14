#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

// Created by Simonhancrew on 2022/03/29

using namespace std;

/*
    先做完最短路之后做一个DFS确定走的顺序
    最短路求解中按照每个亲戚为起点枚举每个亲戚的最短路
    然后在DFS中搜索出所有可能的拜访顺序，然后按照相对应的最短路
    求得最后的解
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 5e4 + 10, M = 2e5 + 10;

int e[M], ne[M], h[N], w[M], idx;
int dis[6][N], rec[6];
bool st[N];
int n, m;

void add(int a, int b, int c) {
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dijstra(int s, int d[]) {
  memset(st, 0, sizeof st);
  memset(d, 0x3f, N * 4);
  priority_queue<PII, vector<PII>, greater<PII>> heap;
  heap.push({0, s});
  while (heap.size()) {
    auto t = heap.top();
    heap.pop();
    int node = t.second, distance = t.first;
    if (st[node]) continue;
    st[node] = true;
    for (int i = h[node]; i != -1; i = ne[i]) {
      int j = e[i];
      if (d[j] > distance + w[i]) {
        d[j] = distance + w[i];
        heap.push({d[j], j});
      }
    }
  }
}

int dfs(int u, int start, int d) {
  if (u > 5) return d;
  int res = INF;
  for (int i = 1; i <= 5; i++) {
    if (!st[i]) {
      int ne = rec[i];
      st[i] = true;
      res = min(res, dfs(u + 1, i, d + dis[start][ne]));
      st[i] = false;
    }
  }
  return res;
}

int main() {
  fast_cin();
  cin >> n >> m;
  rec[0] = 1;
  for (int i = 1; i <= 5; i++) cin >> rec[i];
  memset(h, -1, sizeof h);
  for (int i = 0; i < m; i++) {
    int a, b, t;
    cin >> a >> b >> t;
    add(a, b, t), add(b, a, t);
  }
  for (int i = 0; i < 6; i++) dijstra(rec[i], dis[i]);
  memset(st, 0, sizeof st);
  cout << dfs(1, 0, 0) << endl;
  return 0;
}