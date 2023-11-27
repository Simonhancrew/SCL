#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2022/11/19

using namespace std;

// 算不同子序列的ans = 最大值 - 最小值, 最后对ans求和
// 子序列非常的多，枚举出所有的子序列是指数级复杂度，因此可以转化
// 成为对单点计算贡献值

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, MOD = 1e9 + 7;

int n;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  vector<int> nums(n);
  vector<int> p(n + 1);
  p[0] = 1;
  for (int i = 0; i < n; i++)
    cin >> nums[i];
  for (int i = 1; i <= n; i++)
    p[i] = p[i - 1] * 2 % MOD;
  int res = 0;
  for (int i = 0; i < n; i++) {
    res = (res + (LL)nums[i] * p[i] - (LL)nums[i] * p[n - i - 1]) % MOD;
  }
  cout << res << endl;
  return 0;
}