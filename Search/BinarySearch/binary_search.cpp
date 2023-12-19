#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2023/12/19

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(NULL);                    \
  cout.tie(NULL)

const int INF = 0x3f3f3f3f;

int n, q;

int lower_bound(const vector<int> &arr, int target) {
  auto n = arr.size();
  int l = -1, r = n;
  while (l + 1 < r) {
    int mid = l + r >> 1;
    if (arr[mid] >= target)
      r = mid;
    else
      l = mid;
  }
  return l + 1;
}

int main() {
  fast_cin();
  cin >> n >> q;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  sort(arr.begin(), arr.end());
  while (q--) {
    int target;
    cin >> target;
    auto l = lower_bound(arr, target);
    if (l == n || arr[l] != target) {
      cout << -1 << ' ' << -1 << '\n';
      continue;
    }
    auto r = lower_bound(arr, target + 1) - 1;
    cout << l << ' ' << r << '\n';
  }
  return 0;
}
