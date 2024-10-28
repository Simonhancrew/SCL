#include <iostream>
#include <numeric>
#include <vector>


// Created by Simonhancrew on 2024/10/28

using namespace std;

/*
  from leetcode 685
*/

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int n;
vector<vector<int>> edges;
vector<int> fa;

int find(int x) {
  if (fa[x] != x) {
    fa[x] = find(fa[x]);
  }
  return fa[x];
}

void merge(int x, int y) {
  int fx = find(x);
  int fy = find(y);
  if (fx != fy) {
    fa[fx] = fa[fy];
  }
}

void solve(const vector<vector<int>> edges) {
  vector<int> in(n + 1, 0);
  vector<int> dup;
  for (const auto& e : edges) {
    in[e[1]]++;
  }
  for (int i = 0;i < n;i++) {
    if (in[edges[i][1]] == 2) {
      dup.push_back(i);
    }
  }
  if (!dup.empty()) {
    for (int i = 0;i < n;i++) {
      if (i == dup[1]) {
        continue;
      }
      int x = edges[i][0], y = edges[i][1];
      if (find(x) == find(y)) {
        cout << edges[dup[0]][0] << " " << edges[dup[0]][1] << endl;
        return;
      }
      merge(x, y);
    }
    cout << edges[dup[1]][0] << " " << edges[dup[1]][1] << endl;
    return;
  }
  for(const auto& e : edges) {
    if (find(e[0]) == find(e[1])) {
      cout << e[0] << " " << e[1] << endl;
      return;
    }
    merge(e[0], e[1]);
  }
}


int main() {
  freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  fa.resize(n + 1);
  iota(fa.begin(), fa.end(), 0); 
  for (int i = 0;i < n;i++) {
    int x, y;
    cin >> x >> y;
    edges.push_back({x, y});
  }
  solve(edges);
  return 0;
}