#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/10/09

using namespace std;

// 分开上下两部分，先看上面一部分，在b行中选择i行放置，然后在a列中选择i列，此时顺序有所谓，全shuffule
// 后面的同理，mod是个质数，所以可以用费马小定理，做快速幂逆元然后求解阶乘和组合数

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, P = 100003, N = 2e3 + 10;

int a, b, c, d, k;
int fact[N], infact[N];

int qmi(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = (LL)res * a % P;
    a = (LL)a * a % P;
    b >>= 1;
  }
  return res;
}

int C(int a, int b) {
  if (a < b)
    return 0;
  return (LL)fact[a] * infact[a - b] % P * infact[b] % P;
}

int A(int a, int b) {
  if (a < b)
    return 0;
  return (LL)fact[a] * infact[a - b] % P;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> a >> b >> c >> d >> k;
  fact[0] = infact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i]   = (LL)fact[i - 1] * i % P;
    infact[i] = (LL)infact[i - 1] * qmi(i, P - 2) % P;
  }
  int res = 0;
  for (int i = 0; i <= k; i++) {
    res = ((LL)res +
           (LL)C(b, i) * A(a, i) % P * C(d, k - i) * A(a + c - i, k - i)) %
          P;
  }
  cout << res << '\n';
  return 0;
}