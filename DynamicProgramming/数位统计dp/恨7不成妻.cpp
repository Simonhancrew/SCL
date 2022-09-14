#include <iostream>
#include <vector>

using namespace std;

/*
    迭代的做法
    首先看要求，数位一共三个要求：
    1. 不含有7
    2. 各位数字之和不是7的倍数
    3. 整个数不是7的倍数
    不难想到一个状态定义: f[i][j][a][b],当前一共i位，最高位是j，当前这个数mod 7
   本身是a 这个数的各位之和mod 7的结果是b，当前情况下的平方和
    但是实际上可以展开公式，需要记录当前合法数个数，后合法数的和，后合法数的平方和（0次方，1次方，2次方）
*/

const int N = 20, P = 1e9 + 7;

typedef long long LL;

LL t, l, r;

struct F {
  int s0, s1, s2;
} f[N][10][7][7];

int power7[N], power9[N];

int mod(LL x, int y) { return (x % y + y) % y; }

void init() {
  for (int i = 0; i <= 9; i++) {
    if (i == 7) continue;
    auto &v = f[1][i][i % 7][i % 7];
    v.s0++, v.s1 += i, v.s2 += i * i;
  }
  LL power = 10;
  for (int i = 2; i < N; i++, power *= 10) {
    for (int j = 0; j <= 9; j++) {
      if (j == 7) continue;
      for (int a = 0; a < 7; a++) {
        for (int b = 0; b < 7; b++) {
          for (int k = 0; k <= 9; k++) {
            if (k == 7) continue;
            auto &v1 = f[i][j][a][b];
            auto &v2 = f[i - 1][k][mod(a - j * power, 7)][mod(b - j, 7)];
            v1.s0 = mod(v1.s0 + v2.s0, P);
            v1.s1 = mod(v1.s1 + v2.s1 + j * (power % P) % P * v2.s0,
                        P);  // 放置溢出，power已经大了，要先取模
            v1.s2 =
                mod(v1.s2 + j * j * (power % P) % P * (power % P) % P * v2.s0 +
                        v2.s2 + 2 * j * power % P * v2.s1,
                    P);
          }
        }
      }
    }
  }
  power7[0] = 1, power9[0] = 1;
  for (int i = 1; i < N; i++) {
    power7[i] = power7[i - 1] * 10 % 7;
    power9[i] = power9[i - 1] * 10ll % P;
  }
}

F get(int i, int j, int a, int b) {
  int s0 = 0, s1 = 0, s2 = 0;
  for (int x = 0; x < 7; x++) {
    for (int y = 0; y < 7; y++) {
      if (x != a && y != b) {
        auto v = f[i][j][x][y];
        s0 = (s0 + v.s0) % P;
        s1 = (s1 + v.s1) % P;
        s2 = (s2 + v.s2) % P;
      }
    }
  }
  return {s0, s1, s2};
}

int dp(LL n) {
  if (!n) return 0;
  vector<int> nums;
  LL backup = n % P;
  while (n) {
    nums.push_back(n % 10);
    n /= 10;
  }
  int res = 0;
  // last_a是前缀，last_b是前面位数的和
  LL last_a = 0, last_b = 0;
  for (int i = nums.size() - 1; i >= 0; i--) {
    int x = nums[i];
    for (int j = 0; j < x; j++) {
      if (j == 7) continue;
      int a = mod(-last_a * power7[i + 1], 7);
      int b = mod(-last_b, 7);
      auto v = get(i + 1, j, a, b);
      // 做一次完全平方展开
      res = mod(res +
                    (last_a % P) * (last_a % P) % P * power9[i + 1] % P *
                        power9[i + 1] % P * v.s0 % P +
                    v.s2 + 2 * last_a % P * power9[i + 1] % P * v.s1,
                P);
    }
    if (x == 7) break;
    last_a = last_a * 10 + x;
    last_b += x;
    if (!i && last_a % 7 && last_b % 7) res = (res + backup * backup) % P;
  }
  return res;
}

int main() {
  init();
  cin >> t;
  while (t--) {
    cin >> l >> r;
    cout << mod(dp(r) - dp(l - 1), P) << '\n';
  }
  return 0;
}