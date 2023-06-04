#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2023/06/04

using namespace std;

// from lc 33, 深入理解一下满足二段行的数组都可以二分
// 看一下当前的target是落入那一段，红色是左半边，蓝色是右半边

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e4 + 10;

int n, target;
int a[N];

// 因为数组旋转了，分成了两个递增的数组
// 二分还是能做，只要看看target是划分点的左半边还是右半边
bool check(int i) {
  auto end = a[n - 1];
  // i在左侧数组，判断一下target在当前i的那一侧
  // 这里其实做的是一个lower_bound，只要判断在左侧的条件
  if (a[i] > end) {
    return target > end && a[i] >= target;
  }
  // i在右侧数组，同理判断target在左侧是什么调教
  return target > end || a[i] >= target;
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
  if (a[l] != target) {
    cout << -1 << endl;
    return;
  }
  cout << l << endl;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> target;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  solve();
  return 0;
}
