#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e4 + 10;

int k, a[N];
int dp[N];

// 两个方向各做一遍，不要忘记第二个方向的时候要重新初始化开始长度为1

int main() {
  cin >> k;
  while (k--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int res = 0;
    for (int i = 1; i <= n; i++) {
      dp[i] = 1;
      for (int j = 1; j < i; j++) {
        if (a[i] > a[j]) dp[i] = max(dp[i], dp[j] + 1);
      }
      res = max(res, dp[i]);
    }

    for (int i = n; i >= 1; i--) {
      // 重新初始化dp
      dp[i] = 1;
      for (int j = n; j > i; j--) {
        if (a[i] > a[j]) dp[i] = max(dp[i], dp[j] + 1);
      }
      res = max(res, dp[i]);
    }

    cout << res << endl;
  }
}