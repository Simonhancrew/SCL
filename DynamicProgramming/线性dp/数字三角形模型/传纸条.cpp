#include <algorithm>
#include <iostream>

using namespace std;

const int N = 60;

int w[N][N];
int dp[N * 2][N][N];

/*
    菜鸡菜鸡，可笑可笑。因为确定了非负数，和方格取数一个原理
    dp[k][i][j]，第一位是横纵坐标和，2，3维度是横坐标。意义是花费最大值，确定这个最大值下，一定是两条毫不相交的路径
    否则，相交了，相交的点只能加一次，一条路径往下沉，一定不会等到一个更小的解
    目前让我疑惑的是判断中写if(i != j)可以过，写（i != j || k == 2 || k == m +
   n）也可以过 懵懵懂懂，恍恍惚惚
    最后发现这题的两个端点都卡成0了，简直离谱，想想也确实，自己和自己的好感度凭什么不等于0，2333
*/

int main() {
  int n, m;
  cin >> m >> n;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> w[i][j];
    }
  }

  for (int k = 2; k <= m + n; k++) {
    for (int i = max(1, k - n); i <= min(k - 1, m); i++) {
      for (int j = max(1, k - n); j <= min(k - 1, m); j++) {
        int t = w[i][k - i];
        if (i != j || k == 2 || k == m + n) t += w[j][k - j];
        for (int a = 0; a <= 1; a++) {
          for (int b = 0; b <= 1; b++) {
            dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i - a][j - b] + t);
          }
        }
      }
    }
  }
  cout << dp[m + n][m][m];
}