#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2023/06/03

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10;

int n, q, k;
int a[N];

// 第一种写法，比较好按照循环不变量解释，最后的结果要保证l - 1小于target
// r + 1大于等于target
// 区间左右闭合
// 这种写法，如果值不存在会返回一个超越界限下标的n
int lower_bound(int a[], int tar) {
  int l = 0, r = n - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (a[mid] < tar)
      l = mid + 1;
    else
      r = mid - 1;
  }
  return l;
}

// 第二种写法，r大于等于tar， l - 1小于target
// 这种写法不会超出数据范围，值不存在也会卡在左右边界上
int lower_bound2(int a[], int tar) {
  int l = 0, r = n - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (a[mid] >= tar)
      r = mid;
    else
      l = mid + 1;
  }
  return l;
}

// 这种保证r + 1大于target， l小于等于target
int upper_bound(int a[], int tar) {
  int l = 0, r = n - 1;
  while (l < r) {
    int mid = l + r + 1 >> 1;
    if (a[mid] <= tar)
      l = mid;
    else
      r = mid - 1;
  }
  return l;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> q;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  while (q--) {
    cin >> k;
    auto lhs = lower_bound(a, k);
    if (lhs == n || a[lhs] != k) {
      cout << "-1 -1" << endl;
      continue;
    }
    auto rhs = lower_bound(a, k + 1) - 1;
    cout << lhs << ' ' << rhs << endl;
  }
  return 0;
}
