#include <algorithm>
#include <cstring>
#include <iostream>

// 数字三角形的二维矩阵扩展，只能往两个方向走，不重不漏的套用三角形模型就可以了
// 因为取值是最大，所以可以开大一维，下标从1开始

using namespace std;

const int N = 110;

int dp[N][N], a[N][N];

int r, c;

int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> r >> c;
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= r; i++) {
      for (int j = 1; j <= c; j++) {
        cin >> a[i][j];
      }
    }
    dp[1][1] = a[1][1];
    for (int i = 1; i <= r; i++) {
      for (int j = 1; j <= c; j++) {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + a[i][j];
      }
    }
    cout << dp[r][c] << endl;
  }
  return 0;
}