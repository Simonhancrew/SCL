#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2023/05/28

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10;

int n;
int a[N];

void sort(int a[], int l, int r) {
  if (l >= r)
    return;
  // 保证一个循环不变量, 区间[l, i]范围<=tar, 区间[j, r]范围>=tar
  // 初始的时候区间是空的, 满足要求
  int i = l - 1, j = r + 1, tar = a[l + (r - l) / 2];
  while (i < j) {
    do
      i++;
    while (a[i] < tar);
    do
      j--;
    while (a[j] > tar);
    // 此时a[j] <= tar, q[i] >= tar, 让循环不变式继续满足, 交换ij就好
    if (i < j)
      swap(a[i], a[j]);
  }
  sort(a, l, j), sort(a, j + 1, r);
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  sort(a, 0, n - 1);
  for (int i = 0; i < n; i++)
    cout << a[i] << ' ';
  return 0;
}
