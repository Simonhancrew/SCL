#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/10/11

using namespace std;

// 正例不好求就先求所有的方案，然后求反例，然后相减，求一个补集
// 枚举所有长为i，宽为j的直角三角形，这种三角形一共有(n - i) * (m - j)个(在图上做横移)
// 然后所有的斜边都可以找到了，然后看看这些斜边上有多少个整点，这个范围是gcd(i,j) + 1
// 去掉两个端点，结构就是gcd(i, j) - 1

using LL  = long long;
using PII = pair<int, int>;
#define endl '\n'
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int n,m;

int gcd(int a,int b) {
  return b ? gcd(b, a % b) : a;
}

LL C3(int x) {
  return (LL)(x) * (x - 1) * (x - 2) / 6;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m;
  ++n, ++m; // 格点
  LL res = C3(n * m) - (LL)n * C3(m) - (LL)m * C3(n);
  for(int i = 1;i <= n;i++) {
    for(int j = 1;j <= m;j++) {
      res -= 2ll * (gcd(i,j) - 1) * (n - i) * (m - j);
    }
  }
  cout << res << endl;
  return 0;
}