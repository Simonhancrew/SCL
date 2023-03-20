#include <iostream>

using namespace std;

// 找[1, n]中带重复数字的数的个数
// f[i][j][k], 当前最高位是i, 当前二进制记录重复数字状态是j, 当前是否重复是k(bool)

const int N = 1e9 + 10;

int n;
int a[11], f[11][1024 + 10][2];

void fast_cin() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}

int dfs(int pos, int st, bool succ, bool lead, bool limit) {
  if (!pos) return succ;
  if (!lead && !limit && f[pos][st][succ] != -1) return f[pos][st][succ];
  int res = 0, up = limit ? a[pos] : 9;
  for (int i = 0;i <= up;++i) {
    // 前导0 + 当前位是0的不要考虑
    if (lead && i == 0) {
      res += dfs(pos - 1, st, succ, lead, limit && i == limit);
    } else {
      res += dfs(pos - 1, st | (1 << i), succ | ((st >> i) & 1), lead && !i, limit && i == up);
    }
  }
  return limit ? res : (lead ? res : f[pos][st][succ] = res);
}

int main() {
  fast_cin();
  // freopen("input.txt", "r", stdin);
  cin >> n;
  int len = 0;
  while (n) {
    a[++len] = n % 10;
    n /= 10;
  }
  memset(f, -1, sizeof f);
  cout << dfs(len, 0, 0, 1,1) << '\n';
  return 0;
}

