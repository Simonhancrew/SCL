#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/09/11

using namespace std;

// 思考如何构造矩阵
// sum[i] = sum[i - 1] + i * f[i]
// F[i] = [f[i], f[i + 1], i * f[i], (i + 1) * f[i + 1], sum[i]]
// F[i + 1] = [f[i + 1], f[i + 2], (i + 1) * f[i + 1], (i + 2) * f[i + 2], sum[i + 1]]
// 所以转置矩阵
// A = {{0, 1, 0, 2, 0},
//      {1, 1, 0, 1, 0},
//      {0, 0, 0, 1, 0},
//      {0, 0, 1, 1, 1},
//      {0, 0, 0, 0, 1}};

using LL = long long;
using PII = pair<int, int>;
#define fast_cin()                                                             \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr);                                                            \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 5;


int n, m;

void mul(int f[][N], int a[][N], int b[][N]) {
  static int tmp[N][N];
  memset(tmp, 0, sizeof tmp);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        tmp[i][j] = (tmp[i][j] + (LL)a[i][k] * b[k][j]) % m;
      }
    }
  }
  memcpy(f, tmp, sizeof tmp);
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m;
  int f[N][N] = {1, 1, 1, 2, 1};
  int A[N][N] = {{0, 1, 0, 2, 0},
                 {1, 1, 0, 1, 0},
                 {0, 0, 0, 1, 0},
                 {0, 0, 1, 1, 1},
                 {0, 0, 0, 0, 1}};
  int k = n - 1;
  while (k) {
    if (k & 1)
      mul(f, f, A);
    mul(A, A, A);
    k >>= 1;
  }
  cout << f[0][4] << '\n';
  return 0;
}