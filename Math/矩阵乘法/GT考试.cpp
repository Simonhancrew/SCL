#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/09/26

using namespace std;

// f[i][j], 从起点开始，长度为i，没有匹配成功，与patter匹配长度为j的方案数
// f[i + 1][k] = f[i][j], 其中j能不能转移到k可以用kmp预先做一个跳转
// 发现这个递推关系其实是固定的，这种固定关系可以考虑用矩阵快速幂优化
// f[i + 1][k] = sum(a[i][j] * f[i][j])

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

const int N = 25;

int n, m, mod;
char s[N];
int ne[N];
int a[N][N];

void mul(int a[][N], int b[][N], int c[][N]) {
  static int tmp[N][N];
  memset(tmp, 0, sizeof tmp);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < m; k++) {
        tmp[i][j] = (tmp[i][j] + b[i][k] * c[k][j]) % mod;
      }
    }
  }
  memcpy(a, tmp, sizeof tmp);
}

int qmi(int k) {
  int f[N][N] = {1};
  while (k) {
    if (k & 1)
      mul(f, f, a);
    mul(a, a, a);
    k >>= 1;
  }
  int res = 0;
  for (int i = 0; i < m; i++)
    res = (res + f[0][i]) % mod;
  return res;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m >> mod;
  cin >> s + 1;

  for (int i = 2, j = 0; i <= m; i++) {
    while (j && s[j + 1] != s[i])
      j = ne[j];
    if (s[j + 1] == s[i])
      j++;
    ne[i] = j;
  }

  for (int i = 0; i < m; i++) {
    for (char c = '0'; c <= '9'; c++) {
      int k = i;
      while (k && s[k + 1] != c)
        k = ne[k];
      if (s[k + 1] == c)
        k++;
      if (k < m)
        a[i][k]++;
    }
  }

  cout << qmi(n) << '\n';
  return 0;
}