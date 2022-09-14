#include <iostream>
#include <vector>

using namespace std;

/*
    单纯的数字不能出现前导0，所以需要特判一些位数。
    单纯dp的时候出现前导0无所谓，实际计算的时候不考虑前导0就可以了
    所以在dp过程中还是需要考虑前导0的情况，否则存在无法转移到的情况，比如单一0的时候时可以的
*/

const int N = 11;

int f[N][10];  // 一共i位，最高位是j时的所有可能windy数情况
int l, r;

void init() {
  for (int i = 0; i <= 9; i++) f[1][i] = 1;
  for (int i = 2; i < N; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int k = 0; k <= 9; k++) {
        if (abs(k - j) >= 2) f[i][j] += f[i - 1][k];
      }
    }
  }
}

int dp(int n) {
  if (!n) return 0;
  vector<int> nums;
  while (n) {
    nums.push_back(n % 10);
    n /= 10;
  }
  int last = -2, res = 0;
  for (int i = nums.size() - 1; i >= 0; i--) {
    int x = nums[i];
    for (int j = i == nums.size() - 1; j < x; j++) {
      if (abs(j - last) >= 2) res += f[i + 1][j];
    }
    if (abs(x - last) >= 2)
      last = x;
    else
      break;
    if (!i) res++;
  }
  for (int i = 1; i < nums.size(); i++) {
    for (int j = 1; j <= 9; j++) {
      res += f[i][j];
    }
  }
  return res;
}

int main() {
  init();
  cin >> l >> r;
  cout << dp(r) - dp(l - 1) << '\n';
  return 0;
}