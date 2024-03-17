#include <iostream>
#include <vector>

// Created by Simonhancrew on 2024/03/17

using namespace std;

// 给定一堆无向边，这些边能构成一颗树。要求层高最小的根节点合集
// 类似于树的直径，但是不累加起来，看两边的深度。求出每个节点作为根的最大深度
// 然后过滤出集合

using LL = long long;
using PII = pair<int, int>;
#define fast_cin()                                                             \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr);                                                            \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int n, m;
vector<vector<int>> g;
vector<int> up, d1, d2, rec;

void dfs1(int u, int fa) {
  for (const auto x : g[u]) {
    if (x == fa)
      continue;
    dfs1(x, u);
    auto d = d1[x] + 1;
    if (d >= d1[u]) {
      d2[u] = d1[u];
      d1[u] = d;
      rec[u] = x;
    } else if (d > d2[u]) {
      d2[u] = d;
    }
  }
}

void dfs2(int u, int fa) {
  for (const auto x : g[u]) {
    if (x == fa)
      continue;
    if (rec[u] == x) {
      up[x] = max(up[u], d2[u]) + 1;
    } else {
      up[x] = max(up[u], d1[u]) + 1;
    }
    dfs2(x, u);
  }
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m;
  g.resize(n);
  d1 = d2 = rec = up = vector<int>(n);
  while (m--) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  dfs1(0, -1);
  dfs2(0, -1);
  int mn = n + 1;
  for (int i = 0; i < n; i++) {
    mn = min(mn, max(up[i], d1[i]));
  }
  for (int i = 0; i < n; i++) {
    if (mn == max(up[i], d1[i])) {
      cout << i << ' ';
    }
  }
  cout << '\n';
  return 0;
}
