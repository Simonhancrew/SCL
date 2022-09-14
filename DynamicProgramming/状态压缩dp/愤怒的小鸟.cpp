#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 20, M = 1 << 18;
const double eps = 1e-8;

typedef pair<double, double> PDD;

#define x first
#define y second

PDD p[N];
int f[M];        // 覆盖状态i时刻的最小抛物线数量
int path[N][N];  // 抛物线(i,j)能覆盖的点的状态集合

int cmp(double x, double y) {
  if (fabs(x - y) < eps) return 0;
  if (x < y) return -1;
  return 1;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      cin >> p[i].x >> p[i].y;
    }
    memset(path, 0, sizeof path);
    for (int i = 0; i < n; i++) {
      path[i][i] = 1 << i;  // 只有一个点
      for (int j = 0; j < n; j++) {
        double x1 = p[i].x, y1 = p[i].y;
        double x2 = p[j].x, y2 = p[j].y;
        if (!cmp(x1, x2)) continue;
        double a = (y1 / x1 - y2 / x2) / (x1 - x2);
        double b = y1 / x1 - a * x1;

        if (cmp(a, 0) >= 0) continue;
        int st = 0;
        for (int k = 0; k < n; k++) {
          double x = p[k].x, y = p[k].y;
          if (!cmp(a * x * x + b * x, y)) st += 1 << k;
        }
        path[i][j] = st;
      }
    }

    // 本质是一个爆搜的优化
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int i = 0; i + 1 < 1 << n; i++) {
      int x = 0;
      // 看看那些点没有被覆盖
      for (int j = 0; j < n; j++) {
        if (!(i >> j & 1)) {
          x = j;
          break;
        }
      }
      // 枚举能覆盖x的抛物线，更新最小值
      for (int j = 0; j < n; j++) {
        f[i | path[x][j]] = min(f[i | path[x][j]], f[i] + 1);
      }
    }
    cout << f[(1 << n) - 1] << endl;
  }
  return 0;
}