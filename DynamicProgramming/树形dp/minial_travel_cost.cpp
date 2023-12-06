#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <functional>

// Created by Simonhancrew on 2023/12/06

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(NULL);                    \
  cout.tie(NULL)

const int INF = 0x3f3f3f3f;

int n, m, seats;

// 1. 联通一条路径，这条路径上经过的节点有花费
// 2. 第一次旅行之前可以将一些节点的花费减半
// 3. 求所有花费最小

// 1. 子节点花费计数问题，每个几点经过次数先统计出来
// 2. 从根开始在树上做dp，当前节点不减半，子节点可以减半，也可以不减半，
// 当前节点减半，子节点不能动
// 3. 所以dfs要返回两个值，做一次深搜。


int main() {
  fast_cin();
  cin >> n >> m >> seats;
  vector<vector<int>> g(n);
  for (int i = 0;i < m;i++) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vector<int> price(n); 
  for (int i = 0;i < n;i++) {
    cin >> price[i];
  }
  vector<vector<int>> trips(m);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    trips[i] = {x, y};
  }
  vector<int> cnt(n);
  function<bool(int, int, int)> dfs = [&](int x, int end, int fa) {
    if (x == end) {
      cnt[x]++;
      return true;
    }
    for (const auto y : g[x]) {
      if (y != fa && dfs(y, end, x)) {
        cnt[x]++;
        return true;
      }
    }
    return false;
  };
  for (const auto &p : trips) {
    auto x = p[0], end = p[1];
    dfs(x, end, -1);
  }
  function<PII(int, int)> f = [&](int x, int fa) -> PII {
    int tot      = cnt[x] * price[x];
    int half_tot = tot / 2;
    for (const auto y : g[x]) {
      if (y != fa) {
        PII res = f(y, x);
        tot += min(res.second, res.first);
        half_tot += res.first;
      }
    }
    return {tot, half_tot};
  };
  auto res = f(0, -1);
  cout << min(res.first, res.second) << '\n';
  return 0;
}
