#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2023/06/09

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

string a, b;

auto add(const string &a, const string &b) {
  vector<int> res;
  int n = a.size(), m = b.size();
  int i = 0, acc = 0;
  for (i = 0; i < n && i < m; i++) {
    int cur = (a[i] - '0') + (b[i] - '0') + acc;
    res.push_back(cur % 10);
    acc = cur / 10;
  }
  while (i < n) {
    int cur = (a[i++] - '0') + acc;
    res.push_back(cur % 10);
    acc = cur / 10;
  }
  while (i < m) {
    int cur = (b[i++] - '0') + acc;
    res.push_back(cur % 10);
    acc = cur / 10;
  }
  if (acc)
    res.push_back(acc);
  return res;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> a >> b;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  auto res = add(a, b);
  reverse(res.begin(), res.end());
  for (int i = 0; i < res.size(); i++) {
    cout << res[i];
  }
  cout << '\n';
  return 0;
}
