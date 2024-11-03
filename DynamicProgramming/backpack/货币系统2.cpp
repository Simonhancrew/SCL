#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

// 1. 要找到最小的等价货币系统就是一个删除之前能被小货币组成的大货币的过程
// 2. dp[i][j]前i个数中，能否组成面值j的货币
// 3. 抽象成一个完全背包问题,去掉第一维，第二重便利正向
// 4. 第一重遍历的过程中，如果当前的货币无法组成，直接加入结果集合中

const int N = 25010, M = 110;
int a[M];
int dp[N];
int n;

int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    dp[0] = 1;
    int res = 0, m = a[n - 1];
    for (int i = 0; i < n; i++) {
      if (!dp[a[i]]) res++;
      for (int j = a[i]; j <= m; j++) {
        dp[j] += dp[j - a[i]];
      }
    }
    cout << res << endl;
  }
  return 0;
}