#include <algorithm>
#include <cstring>
#include <iostream>
#include <locale>

// Created by Simonhancrew on 2023/10/16

using namespace std;

// 有两个数出现一次，剩下的出现两次。算一下x ^ y, 然后求一个lowbit
// 这一位在这两个数里一定是不同的，然后就可以分成两组了，分别异或就可以

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10;

int n;
int a[N];

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int pa = 0;
  for (int i = 0; i < n; i++) {
    pa ^= a[i];
  }
  int low = 0;
  // 溢出
  if (pa == INT_MIN) {
    low = pa;
  } else {
    low = pa & (-pa);
  }
  int x = 0, y = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] & low) {
      x ^= a[i];
    } else {
      y ^= a[i];
    }
  }
  cout << x << '\n' << y << '\n';
  return 0;
}
