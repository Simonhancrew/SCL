#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/04/28

using namespace std;

/*
    kruskal应用，首先降二维为一维，能使用并查集
    然后针对连通的边，先将集合合并。
    随后，针对竖直和横向的边分别是不同的权值，将其记录在edge中
    因为最终需要排序，且权值只有1和2，且竖直和横向非常的规则
    可以在加边的时候先加竖直的，再加横向的。
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1010, M = 2 * N * N;

int n, m, cnt;
int x1, y1, x2, y2;
int p[N * N];
int id[N][N];

struct edge {
  int u, v, w;
} e[M];

int find(int x) {
  if (p[x] != x) {
    p[x] = find(p[x]);
  }
  return p[x];
}

// 先加竖直，再加横向的
void get_edge() {
  int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
  int dz[4] = {1, 2, 1, 2};
  // 竖直边在方向数组dz中刚刚好是mod2余0的
  for (int z = 0; z < 2; z++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int u = 0; u < 4; u++) {
          if (u % 2 == z) {
            int x = i + dx[u], y = j + dy[u], w = dz[u];
            if (x && x <= n && y && y <= m) {
              int u = id[i][j], v = id[x][y];
              if (u < v) e[cnt++] = {u, v, w};
            }
          }
        }
      }
    }
  }
}

int main() {
  fast_cin();
  cin >> n >> m;
  for (int i = 1; i <= n * m; i++) p[i] = i;
  for (int i = 1, t = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++, t++) {
      id[i][j] = t;
    }
  }
  while (cin >> x1 >> y1 >> x2 >> y2) {
    int u = find(id[x1][y1]), v = find(id[x2][y2]);
    if (u != v) {
      p[u] = v;
    }
  }

  get_edge();

  int res = 0;
  for (int i = 0; i < cnt; i++) {
    int u = find(e[i].u), v = find(e[i].v);
    int w = e[i].w;
    if (u != v) {
      res += w;
      p[u] = v;
    }
  }

  cout << res << endl;
  return 0;
}