#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e4 + 10;

// 简单的01背包变种，dp[i][j]，前i个数和为j的时候的组合方式
// 两种情况，选和不选当前的数，dp[i - 1][j] + dp[i - 1][j - v[i]]
// 只用到了之前的状态，可以优化成一维的，倒序遍历就可以
// 为什么倒序遍历，因为正序的后面较小的状态是之前几次循环更新出来的，是本层状态

int dp[N], n, m, a;

int main() {
  cin >> n >> m;
  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    cin >> a;
    for (int j = m; j >= a; j--) {
      dp[j] += dp[j - a];
    }
  }
  cout << dp[m] << endl;
}