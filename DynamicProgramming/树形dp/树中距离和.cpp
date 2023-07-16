#include <iostream>
#include <vector>

// Created by Simonhancrew on 2023/07/16

using namespace std;

// 算出树中每个点到其余点的距离之和，然后输出
// 先自底向上，算出每个点到叶子节点的距离和
// 然后自顶向下，算出上半部分的距离和，然后+起来

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10;

int n;
vector<vector<int>> g;
vector<int> up, down, cnt;

void dfs_d(int cur, int pre) {
  for (const auto ne : g[cur]) {
    if (ne == pre)
      continue;
    dfs_d(ne, cur);
    down[cur] += down[ne] + cnt[ne];
    cnt[cur] += cnt[ne];
  }
}

void dfs_u(int cur, int pre) {
  for (const auto ne : g[cur]) {
    if (pre == ne)
      continue;
    up[ne] = up[cur] + down[cur] - (down[ne] + cnt[ne]) + n - cnt[ne];
    dfs_u(ne, cur);
  }
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  cnt.resize(n, 1), up.resize(n), down.resize(n);
  g.resize(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  dfs_d(0, -1);
  dfs_u(0, -1);
  for (int i = 0; i < n; i++) {
    cout << up[i] + down[i] << '\n';
  }
  return 0;
}
