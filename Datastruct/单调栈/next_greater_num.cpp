#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2023/12/12

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(NULL);                    \
  cout.tie(NULL)

const int INF = 0x3f3f3f3f;

int main() {
  fast_cin();
  int n{};
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  vector<int> stk;
  vector<int> ans(n, -1);
  for (int i = 0; i < n; i++) {
    int cur = arr[i];
    while (!stk.empty() && arr[stk.back()] < cur) {
      ans[stk.back()] = cur;
      stk.pop_back();
    }
  }
  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
  return 0;
}
