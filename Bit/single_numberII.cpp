#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2023/10/15

using namespace std;

// 一个数组中的数组，只有一个出现了一次，其余的每个出现x次
// 这种看每一位的贡献，某一位出现了x + 1次则说明一定是1，否则就是0

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 3e4 + 10;

int a[N];
int n;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  int ans = 0;
  for (int i = 0; i < 32; i++) {
    int sum = 0;
    for (int j = 0; j < n; j++) {
      sum += (a[j] >> i) & 1;
    }
    ans += (sum % 3) << i;
  }
  cout << ans << '\n';
  return 0;
}
