#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

// Created by Simonhancrew on 2022/11/19

using namespace std;

// 可以一个循环搞定，奇数中心和偶数中心
// 长度为n的字符串会生成2n - 1组回文中心，逐个枚举

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

string s;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> s;
  int ans = 0, n = s.size();
  for (int i = 0; i < 2 * n - 1; i++) {
    int l = i / 2, r = l + i % 2;
    while (l >= 0 && r < n && s[l] == s[r]) {
      ans++;
      l--, r++;
    }
    cout << ans << endl;
  }
  return 0;
}