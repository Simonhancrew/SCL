#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/10/02

using namespace std;

// f[i]代表以1结尾的最后一个数出现在i位置的方案数
// 因此上一个可能的状态是f[0] .... f[i - k - 1],总方案书取和
// 最后总的方案数就是sum(f[i])
// 在状态转移的过程中，因为加的值是连续的，可以用前缀和优化一下每次状态转移的处理

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1e5 + 10, P = 5000011;

int f[N], s[N];
int n, k;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> k;
  s[0] = f[0] = 1;
  for (int i = 1; i <= n; i++) {
    f[i] = s[max(i - k - 1, 0)];
    s[i] = (s[i - 1] + f[i]) % P;
  }
  cout << s[n] << '\n';
  return 0;
}