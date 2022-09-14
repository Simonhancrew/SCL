#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;
const int N = 1e3 + 10;

int n, m;
int dp[N];

// 正常做就可以了，01当成多重看

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    int v, w, s;
    cin >> v >> w >> s;
    if (s == 0) {
      for (int j = v; j <= m; j++) {
        dp[j] = max(dp[j], dp[j - v] + w);
      }
    } else {
      if (s == -1) s = 1;
      for (int k = 1; k <= s; k *= 2) {
        for (int j = m; j >= k * v; j--) {
          dp[j] = max(dp[j], dp[j - k * v] + k * w);
        }
        s -= k;
      }
      if (s) {
        for (int j = m; j >= s * v; j--) {
          dp[j] = max(dp[j], dp[j - s * v] + s * w);
        }
      }
    }
  }
  cout << dp[m] << endl;
}