#include <algorithm>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2023/09/30

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int n{};

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  vector<int> s;
  s.reserve(n);
  for (int i = 0; i < n; i++) {
    int t;
    cin >> t;
    s.push_back(t);
  }
  sort(s.begin(), s.end());
  LL ans = 0;
  for (LL i = 0, acc = n - 1; i < n; i++, acc--) {
    ans += acc * s[i];
  }
  cout << ans << '\n';
  return 0;
}
