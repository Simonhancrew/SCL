#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 210;

int a[N];
int f[N][N];  // 合并f[l][r]，最后的区间是[l,r]的时候合并的收益，此时len > 2

// 和之前的环形石子合并很像，但是每个石子是有两个信息的，把他展开成环
// 合并(n + 1)长度
// 比如只有两个数的时候，[2,3,2,3],实际合并的就是[3,2,3]这个区间
// f[l][r] = f[l][k] + f[k][r] + a[l] * a[r] * a[k]

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i + n] = a[i];
  }

  memset(f, -0x3f, sizeof f);
  for (int len = 2; len <= n + 1; len++) {
    for (int l = 1; l + len - 1 <= n << 1; l++) {
      int r = l + len - 1;
      if (len == 2)
        f[l][r] = 0;
      else {
        for (int k = l + 1; k < r; k++) {
          f[l][r] = max(f[l][r], f[l][k] + f[k][r] + a[l] * a[k] * a[r]);
        }
      }
    }
  }
  int res = 0;
  for (int i = 1; i <= n; i++) res = max(res, f[i][i + n]);
  cout << res << endl;
}