#include <iostream>
#include <vector>

// Created by Simonhancrew on 2023/12/14

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(NULL);                    \
  cout.tie(NULL)

const int INF = 0x3f3f3f3f;

void add(vector<int> &arr, int l, int r, int x) {
  arr[l] += x;
  if (r + 1 < arr.size()) {
    arr[r + 1] -= x;
  }
}

int main() {
  fast_cin();
  int n{}, m{};
  cin >> n >> m;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    int x{};
    cin >> x;
    add(arr, i, i, x);
  }
  while (m--) {
    int l{}, r{}, c{};
    cin >> l >> r >> c;
    add(arr, l - 1, r - 1, c);
  }
  cout << arr[0] << ' ';
  for (int i = 1; i < n; i++) {
    arr[i] += arr[i - 1];
    cout << arr[i] << ' ';
  }
  cout << '\n';
  return 0;
}
