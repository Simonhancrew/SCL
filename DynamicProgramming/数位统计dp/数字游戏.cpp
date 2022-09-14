#include <iostream>
#include <vector>

using namespace std;

/*
    同样的划归为树形考虑每一位，当前位选择[0,a[i] - 1]和a[i]时分别讨论
    需要预处理的是当前最高位为x时，一共有多少个可能的严格不降数，这里可以用dp处理
    f[i][j]，一共有i位时，最高位时j的时候有多少不降数
    不难知道，i-1位可以选择的数[j,9]，针对每一个数做一个转移就可以了
    f[i][j] = sum(f[i - 1][k]) 其中k在[j,9]
*/

const int N = 15;

int f[N][N], l, r;

void init() {
  for (int i = 0; i <= 9; i++) f[1][i] = 1;

  for (int i = 2; i < N; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int k = j; k <= 9; k++) {
        f[i][j] += f[i - 1][k];
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
    for (int j = last; j < x; j++) {
      res += f[i + 1][j];
    }
    if (x < last) break;
    last = x;
    if (!i) ++res;
  }
  return res;
}

int main() {
  init();
  while (cin >> l >> r) cout << dp(r) - dp(l - 1) << endl;
  return 0;
}