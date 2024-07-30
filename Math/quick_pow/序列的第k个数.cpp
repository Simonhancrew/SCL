#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/08

using namespace std;

/*
    等差： a + c = 2 * b
    等比： a * c = b * b
    化简之后有b = c,既是等比又是等差的情况只有恒等的条件下成立
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int P = 200907;

int t;
int a, b, c, k;

int qmi(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = (LL)res * a % P;
    a = (LL)a * a % P;
    b >>= 1;
  }
  return res;
}

int main() {
  fast_cin();
  cin >> t;
  while (t--) {
    cin >> a >> b >> c >> k;
    if (a + c == 2 * b)
      cout << (a + (LL)(b - a) * (k - 1)) % P << endl;
    else
      cout << (LL)a * qmi(b / a, k - 1) % P << endl;
  }
  return 0;
}