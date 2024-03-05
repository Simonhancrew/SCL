#include <iostream>
#include <limits>
#include <queue>
#include <vector>

// Created by Simonhancrew on 2024/03/05

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int n, m;
vector<vector<PII>> g;

// 统计最短路的方案数目

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m;
  g.resize(n);
  while (m--) {
    int a, b, d;
    cin >> a >> b >> d;
    g[a].emplace_back(b, d);
    g[b].emplace_back(a, d);
  }
  using PIL = pair<int, int64_t>;
  auto cmp  = [](PIL &lhs, PIL &rhs) {
    return lhs.second > rhs.second;
  };
  priority_queue<PIL, vector<PIL>, decltype(cmp)> heap(cmp);
  heap.emplace(0, 0);
  vector<int64_t> dis(n, numeric_limits<int64_t>::max());
  dis[0] = 0;
  vector<int> f(n);
  f[0] = 1;
  while (!heap.empty()) {
    auto [x, dx] = heap.top();
    heap.pop();
    if (x == n - 1) {
      // 确定终点最短路，不会有比这个短的了
      cout << f[x] << '\n';
      break;
    }
    if (dx > dis[x]) {
      continue;
    }
    for (const auto &[y, val] : g[x]) {
      if (dis[y] > dx + val) {
        // 新最短路，从x->y
        dis[y] = dx + val;
        heap.emplace(y, dis[y]);
        f[y] = f[x];
        continue;
      }
      if (dis[y] == dx + val) {
        // 重复最短路
        f[y] = (f[y] + f[x]) % MOD;
      }
    }
  }
  return 0;
}
