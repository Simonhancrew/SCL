#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/10/13

using namespace std;

// 隔板法 + 推公式
// 等价于求序列[a1,a2,a3,....,an]在[L,R]，之间
// 转化x1 = a1, x2 = a2 - a1 ... 
// 求和，x1 + x2 + .. + xn <= R - L 
// 映射，y1 = x1 + 1....
// y1 + y2 + ... + yn <= R - L + n
// 隔板法，C(R - L + n, n)
// n从1到n，求和
// 推公式C(a,b) = C(a - 1, b - 1) + C(a - 1, b)
// 最后的结果就是C(R - L + n + 1, R - L + 1) - 1

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, P = 1e6 + 3;

int t;

int qmi(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = (LL)res * a % P;
    b >>= 1;
    a = (LL)a * a % P;
  }
  return res;
}

int C(int a, int b) {
  if (b > a) {
    return 0;
  }
  int up = 1, down = 1;
  for (int i = 1, j = a; i <= b; i++, j--) {
    up   = (LL)up * j % P;
    down = (LL)down * i % P;
  }
  return (LL)up * qmi(down, P - 2) % P;
}

int lucas(int a, int b) {
  if (a < P && b < P)
    return C(a, b);
  return (LL)lucas(a / P, b / P) * C(a % P, b % P) % P;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> t;
  while (t--) {
    int n, l, r;
    cin >> n >> l >> r;
    cout << (lucas(r - l + n + 1, r - l + 1) + P - 1) % P << '\n';
  }
  return 0;
}
