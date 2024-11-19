#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

// Created by Simonhancrew on 2024/11/19

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int n;
vector<vector<int>> g;

void bfs() {
  vector<int> dis(n, -1);
  dis[0] = 0;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    auto t = q.front();
    q.pop();
    for (const auto ne : g[t]) {
      if (dis[ne] >= 0) {
        continue;
      }
      dis[ne] = dis[t] + 1;
      q.push(ne);
    }
  }
  cout << dis[n - 1] << '\n';
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  g.resize(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
  }
  bfs();
  return 0;
}
