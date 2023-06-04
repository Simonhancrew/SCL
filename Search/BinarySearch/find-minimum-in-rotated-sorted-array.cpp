#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2023/06/04

using namespace std;

// from lc 153, 同样是判断蓝色区间和红色区间，只要a[i] > end, 此时target是整个数组中最小的值
// i一定在左侧的分割数组，要求的targe落在他的右边(蓝色)，此时求lower_bound返回false
// 反之如果a[i]小于end，target一定落在当前[l, r]中mid的左边

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10;

int n;
int a[N];

bool check(int i) {
  auto end = a[i];
  if (a[i] > end) {
    return false;
  }
  return true;
}

void solve() {
  int l = 0, r = n - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (check(mid))
      r = mid;
    else
      l = mid + 1;
  }
  cout << a[l] << endl;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  solve();
  return 0;
}
