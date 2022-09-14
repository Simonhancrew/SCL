#include <algorithm>
#include <iostream>

using namespace std;

const int N = 15;

int w[N][N];
int dp[N * 2][N][N];

// 这是一道摘花生的加强版，要走两次
// 我们这里可以同时走
// dp模型就是dp[i1][j1][i2][j2]，从1，1开始走，分别走到[i1,j1],[i2,j2]的最大取数
// 因为我们最终走的步数是相同的（只能往两个方向走），可以优化掉一维
// dp[k][i1][i2]，走k步的时候（两个都走了k步），分别走到[i1,k -
// i1]和[i2,k-i2]的时候的最大取数
// 针对重合的问题，我们判断两个点是否重合，不重合就 + 两个点的数值
// 此外，还需要判断具体的j1和j2是否合法

int main() {
  int n;
  cin >> n;
  int a, b, c;
  while (cin >> a >> b >> c, a || b || c) w[a][b] = c;

  for (int k = 2; k <= n * 2; k++) {
    for (int i1 = 1; i1 <= n; i1++) {
      for (int i2 = 1; i2 <= n; i2++) {
        int j1 = k - i1, j2 = k - i2;
        // 判断是否合法
        if (j1 >= 1 && j2 >= 1 && j1 <= n && j2 <= n) {
          int t = w[i1][j1];
          if (i1 != i2) t += w[i2][j2];
          int& x = dp[k][i1][i2];
          x = max(x, dp[k - 1][i1 - 1][i2 - 1] + t);  // 两条路都往下
          x = max(x, dp[k - 1][i1 - 1][i2] + t);      // i1往下，i2往右
          x = max(x, dp[k - 1][i1][i2 - 1] + t);
          x = max(x, dp[k - 1][i1][i2] + t);
        }
      }
    }
  }
  cout << dp[2 * n][n][n] << endl;
  return 0;
}