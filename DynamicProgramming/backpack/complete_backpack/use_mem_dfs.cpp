#include <algorithm>
#include <cstring>
#include <iostream>


// Created by Simonhancrew on 2024/11/03

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

constexpr int N = 1e3 + 5;

int n, v;
PII vec[N];
int f[N];

int dfs(int val) {
  if (f[val] != -1) {
    return f[val];
  }
  auto &ans = f[val];
  ans       = 0;
  for (int i = 0; i < n; ++i) {
    auto v = vec[i].first, w = vec[i].second;
    if (v > val) {
      continue;
    }
    ans = max(ans, dfs(val - v) + w);
  }
  return ans;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> v;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    vec[i] = {x, y};
  }
  memset(f, -1, sizeof(int) * (v + 1));
  cout << dfs(v) << '\n';
  return 0;
}
