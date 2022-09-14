#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e3 + 10;
int a[N], dp[N];
int n;

int main() {
  cin >> n;
  int res = 0;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) {
    dp[i] = a[i];
    for (int j = 1; j < i; j++) {
      if (a[i] > a[j]) {
        dp[i] = max(dp[i], dp[j] + a[i]);
      }
    }
    res = max(res, dp[i]);
  }
  cout << res << endl;
  return 0;
}