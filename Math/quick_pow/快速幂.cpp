#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2024/07/30

using namespace std;

using LL  = int64_t;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int n;

LL qmi(int a, int b, int mod) {
  LL res = 1;
  while (b) {
    if (b & 1) {
      res = (res * a) % mod;
    }
    a = (static_cast<LL>(a) * a) % mod;
    b >>= 1;
  }
  return res;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  int a{}, b{}, c{};
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> c;
    cout << qmi(a, b, c) << '\n';
  }
  return 0;
}
