#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/11/21

using namespace std;

// from LC 808
// f[i][j]代表还剩下A的数量是i，b的数量是j的时候的概率
// 因为方案中汤的值都是25的倍数，所以可以缩小一点
// 又因为对于A分汤的期望是大于B的期望很多的因此，在大于一定数值的时候
// 既可以认为A永远先结束

using LL  = long long;
using PII = pair<int, int>;
// #define endl '\n'
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 300;

int n;
int f[N][N];

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  n = (n + 24) / 25;
  if (n >= 200) {
    cout << 1 << endl;
  }
  auto gen = [](int x) {
    return max(0, x);
  };
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (!i && !j)
        f[i][j] = 0.5;
      else if (i && !j)
        f[i][j] = 0;
      else if (!i && j)
        f[i][j] = 1;
      else {
        f[i][j] = (f[gen(i - 4)][j] + f[gen(i - 3)][gen(j - 1)] +
                   f[gen(i - 2)][gen(j - 2)] + f[gen(i - 1)][gen(j - 3)]) /
                  4;
      }
    }
  }
  cout << f[n][n] << endl;
  return 0;
}