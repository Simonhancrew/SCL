#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/08

using namespace std;

/*
    正着想不好想，可以用一个容斥原理
    全部的方案比较好想到，就是m ** n
    合法的方案就是m * (m - 1) * (m - 1) * ---- * (m - 1)
    然后做一个快速幂模板
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int P = 100003;

LL n, m;

int qmi(int a, LL b) {
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
  cin >> m >> n;
  // 处理-数的问题
  cout << (qmi(m, n) - (LL)m * qmi(m - 1, n - 1) % P + P) % P << endl;
  return 0;
}