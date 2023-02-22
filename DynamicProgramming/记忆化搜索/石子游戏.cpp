#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>

// Created by Simonhancrew on 2023/02/22

using namespace std;

// from lc 1140, 先用dfs分析可能的过程
// 让对手能够拿到的石子最少就可以了

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 110;

int n, m;
int p[N], s[N], f[N][N];

int dfs(int st, int x) {
  if (st + 2 * x >= n + 1)
    return s[n] - s[st - 1];
  auto &rec = f[st][x];
  if (rec != -1)
    return rec;
  int mn = numeric_limits<int>::max();
  for (int i = 1; i <= 2 * x; i++) {
    mn = min(mn, dfs(st + i, max(i, x)));
  }
  return f[st][x] = s[n] - s[st - 1] - mn;
}

int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  memset(f, -1, sizeof f);
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    cin >> p[i];
  for (int i = 1; i <= n; i++)
    s[i] = s[i - 1] + p[i - 1];
  cout << dfs(1, 1) << endl;
  return 0;
}