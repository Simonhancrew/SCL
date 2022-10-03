#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/10/03

using namespace std;

// 隔板法的应用，首先快速幂算出x ^ x = n
// 考虑隔板法，一共有n个球，分摊到k个盒子，且不能为空
// 等价于在n - 1个缝隙中，选择k - 1个缝隙

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 150;

int k, x;
int f[1000][100][N];

int qmi(int a, int b, int p) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = (LL)(res * a) % p;
    a = a * a % p;
    b >>= 1;
  }
  return res;
}

void add(int a[], int b[], int c[]) {
  for (int i = 0, t = 0; i < N; i++) {
    t += b[i] + c[i];
    a[i] = t % 10;
    t /= 10;
  }
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> k >> x;
  int n = qmi(x % 1000, x, 1000);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i && j < k; j++) {
      if (!j)
        f[i][j][0] = 1;
      else
        add(f[i][j], f[i - 1][j - 1], f[i - 1][j]);
    }
  }
  auto g  = f[n - 1][k - 1];
  int idx = N - 1;
  while (!g[idx])
    --idx;
  while (idx >= 0)
    cout << g[idx--];
  return 0;
}