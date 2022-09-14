#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 11, M = 110;

/*
    难点还是在初始化的时候，同样将每一位树形分析
    选定某一位时[0,ai - 1]的时候，当前分支的方案数如何确定？
    同样需要结合dp，f[i][j][k]，当前一共i位，最高位是j时，且所有数mod
   p的和是k时的结果 不难知道f[i][j][k] = sum(f[i - 1][x][mod(k - j,p)])
    一个递推的关系就可以形成
*/

int l, r, P;
int f[N][10][M];

int mod(int x, int y) { return (x % y + y) % y; }

void init() {
  memset(f, 0, sizeof f);
  for (int i = 0; i <= 9; i++) f[1][i][i % P]++;
  for (int i = 2; i < N; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int k = 0; k < P; k++) {
        for (int x = 0; x <= 9; x++) {
          f[i][j][k] += f[i - 1][x][mod(k - j, P)];
        }
      }
    }
  }
}

int dp(int n) {
  if (!n) return 1;
  vector<int> nums;
  while (n) {
    nums.push_back(n % 10);
    n /= 10;
  }
  int last = 0, res = 0;
  for (int i = nums.size() - 1; i >= 0; i--) {
    int x = nums[i];
    for (int j = 0; j < x; j++) {
      res += f[i + 1][j][mod(-last, P)];
    }
    last += x;
    if (!i && last % P == 0) ++res;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  while (cin >> l >> r >> P) {
    init();
    cout << dp(r) - dp(l - 1) << '\n';
  }
  return 0;
}