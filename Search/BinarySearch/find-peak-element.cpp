#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2023/06/04

using namespace std;

// from lc 162, 峰顶元素左侧都是红色区域， 右侧都是蓝色区域

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
  if (a[i] <= a[i + 1]) {
    return false;
  }
  return true;
}

void solve() {
  if (n == 1) {
    cout << 0 << endl;
    return;
  }
  int l = 0, r = n - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (check(mid))
      r = mid;
    else
      l = mid + 1;
  }
  cout << l << endl;
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
