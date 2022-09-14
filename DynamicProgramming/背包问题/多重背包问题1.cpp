#include <algorithm>
#include <iostream>

//多重背包问题，同一个重量和value的物品有n件
//所以朴素的解法和多重背包是很类似的

using namespace std;

// 二维的比较单一
const int N = 110;

#ifdef TWODIM

int v[N], w[N], s[N];
int dp[N][N];

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> v[i] >> w[i] >> s[i];

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      for (int k = 0; k <= s[i] && k * v[i] <= j; k++) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - k * v[i]] + k * w[i]);
      }
    }
  }
  cout << dp[n][m] << endl;
  return 0;
}
#endif

// 因为当前行之和上一行有关系，所以参考01背包的优化，可以优化成反向遍历体积的一位转移方程

int dp[N];
int v[N], w[N], s[N];
int n, m;

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    int v, w, s;
    cin >> v >> w >> s;
    for (int j = m; j >= 0; j--) {
      for (int k = 1; k <= s && k * v <= j; k++)
        dp[j] = max(dp[j], dp[j - k * v] + w * k);
    }
  }
  cout << dp[m] << endl;
}