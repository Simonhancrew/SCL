#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <vector>

// Created by Simonhancrew on 2023/08/13

using namespace std;

// 1是小偷，问从(0, 0)走到(n - 1, n - 1)的最大安全系数
// 安全系数的定义是路径中的点到附近最近的小偷的曼哈顿距离的最大值
// 一个套路就是先对小偷做多源BFS，算出各个点到小偷的距离，对相同距离的分在一个组里
// 随后倒叙遍历这个集合，对每个组的点做合并集合，判断起点和终点有没有联通

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 400 + 10;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int fa[N * N];
int grid[N][N];
int n;


int get(int x, int y) {
  return x * n + y;
}

int find(int x) {
  if (x != fa[x]) {
    fa[x] = find(fa[x]);
  }
  return fa[x];
}

void merge(int x, int y) {
  if (find(x) == find(y)) {
    return;
  }
  fa[find(x)] = find(y);
}


int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> grid[i][j];
    }
  }
  vector<PII> q;
  vector<vector<int>> dis(n, vector<int>(n, -1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 1) {
        q.emplace_back(i, j);
        dis[i][j] = 0;
      }
    }
  }
  vector<vector<PII>> gr{q};
  while (q.size()) {
    vector<PII> ne;
    for (const auto &[x, y] : q) {
      for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= n || ny >= n)
          continue;
        if (dis[nx][ny] >= 0)
          continue;
        dis[nx][ny] = gr.size();
        ne.emplace_back(nx, ny);
      }
    }
    if (ne.empty()) {
      break;
    }
    gr.emplace_back(ne);
    q = std::move(ne);
  }
  iota(fa, fa + n * n, 0);
  for (int id = gr.size() - 1;id >= 0;id--) {
    const auto &cur = gr[id];
    for (const auto& [x, y] : cur) {
      for (int i = 0;i < 4;i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
        if (dis[nx][ny] < dis[x][y]) continue;
        merge(get(x, y), get(nx, ny));
      }
    }
    if (find(0) == find(get(n - 1, n - 1))) {
      cout << id << endl;
      break;
    }
  }
  return 0;
}
