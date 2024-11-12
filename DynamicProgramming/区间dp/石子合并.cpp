#include <algorithm>
#include <iostream>
#include <climits>
#include <cstring>

// Created by Simonhancrew on 2024/11/12

using namespace std;

/*
枚举左右端

`[l, r]`的合并的代价=`[l, mid]`合并代价 + `[mid + 1, r]`合并代价 + `[l, r]`最后一次合并合成一堆的代价

最后一次的代价可以用前缀和优化
*/

using LL = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 310;

int n;
int a[N];
int f[N][N];

int dfs(int l, int r) {
  if (l >= r) {
    return 0;
  }
  auto& res = f[l][r];
  if (res != -1) {
    return res;
  }
  res = INT_MAX;
  auto sum = a[r] - a[l - 1];
  for (int mid = l; mid < r; mid++) {
    res = min(res, dfs(l, mid) + dfs(mid + 1, r) + sum);
  }
  return res;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i] += a[i - 1];
  }
  memset(f, -1, sizeof f);
  cout << dfs(1, n) << '\n';
  return 0;
}
