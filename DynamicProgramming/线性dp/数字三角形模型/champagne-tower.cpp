#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/11/20

using namespace std;

// 倒香槟，从上往下算

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e3 + 10;

int n, m, k;
double f[N][N];

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m >> k;
  f[0][0] = k;
  for(int i = 0;i < n;i++) {
    for(int j = 0;j <= i;j++) {
      if (f[i][j] > 1) {
        double x = (f[i][j] - 1) / 2;
        f[i + 1][j] += x, f[i + 1][j + 1] += x;
      }
    }
  }
  cout << min(f[n][m], 1.0) << endl;
  return 0;
}