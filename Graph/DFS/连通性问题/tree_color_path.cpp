#include <time.h>
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

// 针对树，在回溯的时候带上路径找到的信息
// 如果是图，需要用bfs，如果带权，需要用最短路

int n, m;

int main() {
  fast_cin();
  cin >> n >> m;
  vector<vector<int>> edge;
  edge.reserve(m);
  while (m--) {
    int x, y;
    cin >> x >> y;
    edge.push_back({x, y});
  }
  m = edge.size();
  vector<vector<int>> g(n);
  for (int i = 0;i < m;i++) {
    auto x = edge[i][0], y = edge[i][1];
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vector<int> color(n, 0);
  int path_cnt = 0;
  cin >> path_cnt;
  function<bool(int, int, int)> dfs = [&](int x, int fa, int end) {
    if (x == end) {
      color[x] += 1;
      return true;
    }
    for (const auto y : g[x]) {
      if (y == fa) continue;
      if (dfs(y, x, end)) {
        color[x] += 1;
        return true;
      }
    }
    return false;
  };
  while (path_cnt--) {
    int x, y;
    cin >> x >> y;
    dfs(x, -1, y);
  }
  for (const auto x : color) {
    cout << x << " ";
  }
  return 0;
}
