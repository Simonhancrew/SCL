#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>

// Created by Simonhancrew on 2023/01/07

using namespace std;

// from lc 1658, 左边增则右边减小，一个双指针

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;
const int N = 1e5 + 10;

int n,x;
int p[N];

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> x;
  for (int i = 0; i < n; i++)
    cin >> p[i];
  int lhs = 0, rhs = accumulate(p, p + n, 0);
  if (rhs < x) {
    cout << -1 << endl;
    return 0;
  }
  int ans = INF;
  for (int l = -1, r = 0; l < n; l++) {
    if (l != -1) {
      lhs += p[l];
    }
    while (r < n && lhs + rhs > x) {
      rhs -= p[r];
      r++;
    }
    if (lhs + rhs == x) {
      ans = min(ans, l + 1 + n - r);
    }
  }
  if (ans == INF) {
    cout << -1 << endl;
    return 0;
  }
  cout << ans << endl;
  return 0;
}