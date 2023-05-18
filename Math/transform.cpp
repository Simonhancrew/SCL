#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

// Created by Simonhancrew on 2023/05/18

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int n, base;

// 短除法
string trans(int n, int base) {
  if (!n)
    return "0";
  bool nag = false;
  if (n < 0) {
    nag = true;
    n   = -n;
  }
  string res;
  while (n) {
    int cur = abs(n % base);
    res += to_string(cur);
    n = (n - cur) / base;
  }
  if (nag)
    res.push_back('-');
  reverse(res.begin(), res.end());
  return res;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> base;
  cout << trans(n, base) << '\n';
  return 0;
}