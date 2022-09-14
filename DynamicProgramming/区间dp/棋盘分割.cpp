#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 9, M = 15;
const double INF = 1e9;

// 求均方差最小等价于将所有的平方差求和除以n取根号

int n, m = 8;
int s[N][N];
double f[N][N][N][N][M];  // 左上角x1,y1,右下角x2,y2,划分到k-1的矩阵的方差值最小
double X;  //均值x拔

// 方差
double get(int x1, int y1, int x2, int y2) {
  //根号下，求和符号内的部分
  double sum =
      s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1] - X;
  //还要平方
  return (double)sum * sum;
}

double dp(int x1, int y1, int x2, int y2, int k) {
  auto &t = f[x1][y1][x2][y2][k];
  if (t >= 0) return t;
  if (k == 1) return get(x1, y1, x2, y2);

  t = INF;  //求最小值要初始化成最大值
  //横着切
  for (int i = x1; i < x2; ++i) {
    t = min(t, dp(x1, y1, i, y2, k - 1) + get(i + 1, y1, x2, y2));
    t = min(t, dp(i + 1, y1, x2, y2, k - 1) + get(x1, y1, i, y2));
  }
  //竖着切
  for (int i = y1; i < y2; ++i) {
    t = min(t, dp(x1, y1, x2, i, k - 1) + get(x1, i + 1, x2, y2));
    t = min(t, dp(x1, i + 1, x2, y2, k - 1) + get(x1, y1, x2, i));
  }
  return t;
}

int main() {
  cin >> n;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> s[i][j];
      s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    }
  }
  X = (double)s[m][m] / n;
  //记忆化搜索，初始化成NaN
  memset(f, -1, sizeof f);

  printf("%.3lf\n", sqrt(dp(1, 1, m, m, n) / n));
  return 0;
}