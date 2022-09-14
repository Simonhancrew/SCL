#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

/*
    感觉和DP关系不大，针对一个二维区间的最大最小值，转化为一维的。
    因为给定了一个正方形的大小为k，所以可以将rom_max[x][j]设为（i，j）和其左侧k个格子中的最大值
    可以用单调队列处理。同理处理一个row_min
    然后遍历时，从k到m，k到n
    针对每列，处理一个当前(i,j)点，到上方k个格子之间的最大最小值，然后就可以转化成一个线性问题
*/

const int N = 1e3 + 10, INF = 0x3f3f3f3f;

#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)

int q[N], w[N][N];
int row_max[N][N], row_min[N][N];
int n, m, k;

void get_max(int a[], int b[], int cnt) {
  int hh = 0, tt = -1;
  for (int i = 1; i <= cnt; i++) {
    if (hh <= tt && q[hh] <= i - k) hh++;
    while (hh <= tt && a[q[tt]] <= a[i]) tt--;
    q[++tt] = i;
    b[i] = a[q[hh]];
  }
}

void get_min(int a[], int b[], int cnt) {
  int hh = 0, tt = -1;
  for (int i = 1; i <= cnt; i++) {
    if (hh <= tt && q[hh] <= i - k) hh++;
    while (hh <= tt && a[q[tt]] >= a[i]) tt--;
    q[++tt] = i;
    b[i] = a[q[hh]];
  }
}

int main() {
  fast_cin();
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> w[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    get_max(w[i], row_max[i], m);
    get_min(w[i], row_min[i], m);
  }
  int res = INF;
  int a[N], b[N], c[N];
  for (int i = k; i <= m; i++) {
    for (int j = 1; j <= n; j++) a[j] = row_max[j][i];
    get_max(a, b, n);
    for (int j = 1; j <= n; j++) a[j] = row_min[j][i];
    get_min(a, c, n);
    for (int j = k; j <= n; j++) res = min(res, b[j] - c[j]);
  }
  cout << res << endl;
}