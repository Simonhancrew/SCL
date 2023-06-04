#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2023/06/04

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

double n;

// 浮点数都是整除，可以严格缩小一半的区间

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  double l = -1000, r = 1000;
  while (r - l > 1e-8) {
    auto mid = (l + r) / 2;
    if (mid * mid * mid >= n)
      r = mid;
    else
      l = mid;
  }
  printf("%.6lf\n", l);
  return 0;
}
