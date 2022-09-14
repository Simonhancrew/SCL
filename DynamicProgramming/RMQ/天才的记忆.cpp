#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const int N = 2e5 + 10, M = 18;

/*
    range min/max query，实质上本体实质一个dp的预处理
    f[i][j]是从i开始，区间长度2**j的范围区间中的最值
    可以通过折半分治求得(前一半的最值和后一半的最值)
    f[i][j] = max(f[i][j - 1],f[i + 1 << j - 1][j - 1])
    最后在区间[l,r]求解的时候为了完美覆盖整个区间,就是2 ** k
    和后2 ** k做一个max就行
    query(l,r):
        len = r - l + 1
        k = log2(len)
        return max(f[l][k],f[r - (1 << k) + 1][k]);
*/

int n, m;
int l, r;
int w[N];
int f[N][M];

void init() {
  for (int j = 0; j < M; j++) {
    for (int i = 0; i + (1 << j) - 1 < n; i++) {
      if (!j)
        f[i][j] = w[i];
      else
        f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
    }
  }
}

int query(int l, int r) {
  int len = r - l + 1;
  int k = log(len) / log(2);
  return max(f[l][k], f[r - (1 << k) + 1][k]);
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> w[i];
  init();
  cin >> m;
  while (m--) {
    cin >> l >> r;
    l--, r--;
    cout << query(l, r) << endl;
  }
  return 0;
}