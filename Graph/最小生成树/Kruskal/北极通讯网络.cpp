#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/04/30

using namespace std;

/*
    等价于将大于d的边删除，使得图形连通块的个数不超过k
    kruskal最初的时候会有n个连通块，且边权正好是升序的，在每次合并中，连通块的数量会
    减少1，最终当联通块刚好为k的时候就找到了一个最小的d。
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

#define x first
#define y second

const int INF = 0x3f3f3f3f, N = 510, M = N * N / 2;

int n, k, idx;
PII q[N];
int p[N];

struct edge {
  int u, v;
  double w;
} e[M];

double get_dist(PII a, PII b) {
  int dx = a.x - b.x;
  int dy = a.y - b.y;
  return sqrt(dx * dx + dy * dy);
}

int find(int x) {
  if (p[x] != x) {
    p[x] = find(p[x]);
  }
  return p[x];
}

int main() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> q[i].x >> q[i].y;
  for (int i = 0; i < n; i++) p[i] = i;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      // if(i == j) continue;
      e[idx++] = {i, j, get_dist(q[i], q[j])};
    }
  }

  int cnt = n;
  double res = 0;
  sort(e, e + idx, [](edge &lhs, edge &rhs) { return lhs.w < rhs.w; });

  for (int i = 0; i < idx; i++) {
    if (cnt <= k) break;
    int u = find(e[i].u), v = find(e[i].v);
    double w = e[i].w;
    if (u != v) {
      p[u] = v;
      cnt--;
      res = w;
    }
  }
  printf("%.2lf\n", res);
  return 0;
}