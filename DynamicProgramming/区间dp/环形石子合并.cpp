#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 410, INF = 0x3f3f3f3f;

int n;
int a[N], s[N];
int f[N][N], g[N][N];

// 考虑之前的直线型石子合并，环形的话处理两种思路，
// 一个是枚举环中分开的位置（合并的时候连接一条链，一共会连接n-1条链）
// 第二种就是把链延长两倍，然后直接套区间dp的模板
// 第一种会多一维循环，复杂度太高
// 拆环成链的思路

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i], a[i + n] = a[i];
  for (int i = 1; i <= n << 1; i++) s[i] = s[i - 1] + a[i];

  memset(f, 0x3f, sizeof f);
  memset(g, -0x3f, sizeof g);

  for (int len = 1; len <= n; len++) {
    for (int l = 1; l + len - 1 <= n << 1; ++l) {
      int r = l + len - 1;
      if (len == 1)
        f[l][r] = g[l][r] = 0;
      else {
        for (int k = l; k < r; k++) {
          f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
          g[l][r] = max(g[l][r], g[l][k] + g[k + 1][r] + s[r] - s[l - 1]);
        }
      }
    }
  }
  int mx = -INF, mn = INF;
  for (int i = 1; i <= n; i++) {
    mx = max(mx, g[i][i + n - 1]);
    mn = min(mn, f[i][i + n - 1]);
  }
  cout << mn << endl << mx << endl;
  return 0;
}