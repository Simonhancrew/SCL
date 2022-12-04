#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>

// Created by Simonhancrew on 2022/12/04

using namespace std;

// from lc 1774
// 答案可能来自与target两边，因此分别考虑就行了
// >= target的是base和base + extra里最小的大于target的值
// 左边比tar小的， 转化为一个01背包问题，f[i]代表价值为i的能否被凑出来
// 所以f[i] |= f[i - v]， 因为一个extra可以选两次，单纯当成有两件去做

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 20, M = 1e4 + 10;

int n, m, tar;
int base[N], extra[N];
int f[M];

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m >> tar;
  for (int i = 0; i < n; i++)
    cin >> base[i];
  for (int i = 0; i < m; i++)
    cin >> extra[i];
  int res = numeric_limits<int>::max();
  // 单个合法解 + target右边单个的最小值
  for (auto x : base) {
    if (x > tar) {
      res = min(res, tar);
    } else {
      f[x] = true;
    }
  }
  if (f[tar]) {
    cout << tar << endl;
    return;
  }
  // 01背包求左边合法解
  // 配合求出target右边的组合合法解
  for (auto t : extra) {
    for (int i = 0; i < 2; i++) {
      for (int j = tar; j > t; j--) {
        // j能在上一波被凑出，j + t可能出现在答案中
        if (f[j] && j + t > tar) {
          res = min(res, j + t);
        }
        if (!f[j] && j - t > 0) {
          f[j] |= f[j - t];
        }
      }
    }
  }
  bool flag = true;
  // 针对左边的解，到target的距离
  // 要比右边的到target的小或者等才合法
  for (int i = 0; i <= res - tar && i <= tar; i++) {
    if (f[tar - i]) {
      cout << tar - i << '\n';
      flag = false;
    }
  }
  if (flag) {
    cout << res << '\n';
  }
  return 0;
}