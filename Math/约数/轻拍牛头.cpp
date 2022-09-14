#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/10

using namespace std;

/*
    每个数的范围在1e6以内，暴力的做是一个N ** 2的复杂度
    求约数是比较难的，但是求倍数是比较简单的，1e6范围内的
    在给出的数组A的条件下，每个数的约数有多少个就行了（在倍增中做）
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e6 + 10;

int n;
int a[N], cnt[N], s[N];

int main() {
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    cnt[a[i]]++;
  }
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
      s[j] += cnt[i];
    }
  }
  // 除掉自己本身
  for (int i = 0; i < n; i++) cout << s[a[i]] - 1 << endl;
  return 0;
}