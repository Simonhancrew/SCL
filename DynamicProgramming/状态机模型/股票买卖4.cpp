#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e5 + 10, M = 110;

int f[N][M][2];
int w[N];
int n, m;

// f[i][j][1/0]前i天，进行了j次交易，是否持有股票的情况下的最大收益

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> w[i];
  memset(f, -0x3f, sizeof f);
  for (int i = 0; i <= n; i++) f[i][0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1] + w[i]);
      f[i][j][1] = max(f[i - 1][j][1], f[i - 1][j - 1][0] - w[i]);
    }
  }
  int res = 0;
  for (int i = 0; i <= m; i++) res = max(res, f[n][i][0]);
  cout << res << endl;
}