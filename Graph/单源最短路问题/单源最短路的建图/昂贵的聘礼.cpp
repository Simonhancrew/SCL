#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/27

using namespace std;

/*
    建图的问题，超极原点设为初始起点
    然后按照要求设置每个节点的转移代价
    关于不能超过要求的等级，直接多次枚举每一个可能的
    等级区间就可以了，然后对每一个等级区间做一次dijstra
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 110;

int n, m;
int g[N][N], d[N];  // 转移代价和最短路
int level[N];       // 每个节点的等级
bool st[N];         // dij确定距离的集合

int dijstra(int l, int r) {
  memset(st, 0, sizeof st);
  memset(d, 0x3f, sizeof d);
  d[0] = 0;
  for (int i = 0; i < n; i++) {
    int t = -1;
    for (int j = 0; j <= n; j++) {
      if (!st[j] && (t == -1 || d[t] > d[j])) {
        t = j;
      }
    }
    st[t] = true;
    for (int j = 0; j <= n; j++) {
      if (level[j] >= l && level[j] <= r) {
        d[j] = min(d[j], d[t] + g[t][j]);
      }
    }
  }
  return d[1];
}

int main() {
  fast_cin();
  cin >> m >> n;
  memset(g, 0x3f, sizeof g);
  for (int i = 1; i <= n; i++) g[i][i] = 0;
  for (int i = 1; i <= n; i++) {
    int p, l, x;
    cin >> p >> level[i] >> x;
    g[0][i] = min(g[0][i], p);
    while (x--) {
      int t, v;
      cin >> t >> v;
      g[t][i] = min(v, g[t][i]);
    }
  }
  int res = INF;
  for (int i = level[1] - m; i <= level[1]; i++)
    res = min(res, dijstra(i, i + m));
  cout << res << endl;
  return 0;
}