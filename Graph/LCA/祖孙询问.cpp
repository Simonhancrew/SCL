#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/05/15

using namespace std;

/*
    一道LCA的裸题，首先建图，然后添加一个虚拟根节点考虑边界
    之后用一个bfs建立depth数组和fa的递增关系
    其中fa[i][k]代表节点i向上走2^k步的节点,则fa[i][k] = fa[fa[i][k - 1]][k - 1]
    在求解的时候先让x和y跳到同一层上，随后一起网上找f[x][k] != f[y][k]的点，更新
    这一步也是从大到小的，保证最后的结果是lca(x,y)的下一层(x,y)，最后跳到f[x][0]的位置就是答案了
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 4e4 + 10, M = 17;

int n, m;
int h[N], e[N * 2], ne[N * 2], idx;
int fa[N][M];
int depth[N], q[N];

void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

void bfs(int root) {
  memset(depth, 0x3f, sizeof depth);  // 因为是无向图，BFS需要做点处理
  depth[0] = 0, depth[root] = 1;
  int hh = 0, tt = -1;
  q[++tt] = root;
  while (hh <= tt) {
    int t = q[hh++];
    for (int i = h[t]; i != -1; i = ne[i]) {
      int j = e[i];
      if (depth[j] > depth[t] + 1) {
        depth[j] = depth[t] + 1;
        q[++tt] = j;
        fa[j][0] = t;
        for (int k = 1; k <= 15; k++) {
          fa[j][k] = fa[fa[j][k - 1]][k - 1];
        }
      }
    }
  }
}

int lca(int a, int b) {
  if (depth[a] < depth[b]) swap(a, b);
  for (int i = 16; i >= 0; i--) {
    if (depth[fa[a][i]] >= depth[b]) {
      a = fa[a][i];
    }
  }
  if (a == b) return a;
  for (int i = 16; i >= 0; i--) {
    if (fa[a][i] != fa[b][i])  // 跳的步数是从大到小的
    {
      a = fa[a][i];
      b = fa[b][i];
    }
  }
  return fa[a][0];
}

int main() {
  fast_cin();
  cin >> n;
  int root = 0;
  memset(h, -1, sizeof h);
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    if (b == -1)
      root = a;
    else
      add(a, b), add(b, a);
  }
  bfs(root);
  cin >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    int p = lca(a, b);
    if (p == a)
      cout << 1 << endl;
    else if (p == b)
      cout << 2 << endl;
    else
      cout << 0 << endl;
  }
  return 0;
}