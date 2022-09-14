#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

/*
    1 针对每个节点求一个向下的最长路径和次长路径
    2
   针对每个节点求一个向上(看似向上，其实是当前点的可继续深搜方向)的最长路径，如果当前最长路径是和之前向下的最长路径一个方向来的话，就要用次长路径更新
    整体 up[j] = max(up[u],d1[u]) + w[i] or up[j] = max(up[u],d2[u]) + w[i];
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1e4 + 10, M = 2 * N, INF = 0x3f3f3f3f;

int e[M], ne[M], h[N], w[M], idx;
int n;
int d1[N], d2[N], p1[N], up[N];
int is_leaf[N];

void add(int a, int b, int c) {
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dfs_d(int u, int father) {
  d1[u] = d2[u] = -INF;
  for (int i = h[u]; i != -1; i = ne[i]) {
    int j = e[i];
    if (j == father) continue;
    int d = dfs_d(j, u) + w[i];
    if (d >= d1[u]) {
      d2[u] = d1[u];
      d1[u] = d;
      p1[u] = j;
    } else if (d > d2[u])
      d2[u] = d;
  }
  if (d1[u] == -INF) {
    d1[u] = d2[u] = 0;
    is_leaf[u] = true;
  }
  return d1[u];
}

void dfs_u(int u, int father) {
  for (int i = h[u]; i != -1; i = ne[i]) {
    int j = e[i];
    if (j == father) continue;

    if (p1[u] == j)
      up[j] = max(up[u], d2[u]) + w[i];
    else
      up[j] = max(up[u], d1[u]) + w[i];

    dfs_u(j, u);
  }
}

int main() {
  fast_cin();
  cin >> n;
  memset(h, -1, sizeof h);
  for (int i = 1; i < n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    add(a, b, c), add(b, a, c);
  }
  dfs_d(1, -1);
  dfs_u(1, -1);

  int res = d1[1];
  for (int i = 2; i <= n; i++) {
    if (is_leaf[i])
      res = min(res, up[i]);
    else
      res = min(res, max(d1[i], up[i]));
  }
  cout << res << endl;
  return 0;
}