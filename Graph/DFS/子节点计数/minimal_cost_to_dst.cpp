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

// 每个子节点要到根，看作一个个人。但是现在可以坐车，一辆车限载，车上路过一条边的花费是恒定的
// 所以看看每个节点底下汇聚了多少人，其上行边的花费就是当前聚集人数 / 车位，根没有上行边，所以要刨除根
// 这是一类树节点计数->递归结束之后返回计算代价的题目

int n, m, seats;

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
  int ans = 0;
  function<int(int, int)> dfs = [&](int x, int fa) {
    int size = 1;
    for (const auto y : g[x]) {
      if (y == fa)
        continue;
      size += dfs(y, x);
    }
    if (x != 0) {
      ans += (size + seats - 1) / seats;
    }
    return size;
  };
  dfs(0, -1);
  cout << ans << '\n';
  return 0;
}
