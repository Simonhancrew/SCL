#include <algorithm>
#include <cstring>
#include <iostream>

// dp[i][j]，s1的前i和s2的前j的最长公共子序列是多少

using namespace std;

const int N = 1e3 + 10;
int dp[N][N];
char a[N], b[N];

int main() {
  // freopen("input.txt", "r", stdin);
  int m, n;
  cin >> m >> n;
  scanf("%s%s", a + 1, b + 1);
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      if (a[i] == b[j]) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
    }
  }
  cout << dp[m][n] << endl;
  int i = m, j = n;
  string ans;
  auto&f = dp;
  while (i > 0 && j > 0) {
    if (a[i] == b[j]) {
      ans += a[i];
    } else if (f[i][j] == f[i - 1][j]) {
      i--;
    } else if (f[i][j] == f[i][j - 1]) {
      j--;
    }
  }
  reverse(ans.begin(), ans.end());
  cout << ans << endl;
  return 0;
}
