#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2021/10/26

using namespace std;

const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int a[N], f[N][3];
int n;

// f[i][0],f[i][1],f[i][2],手中有货 | 手中无货的第一天，不可买入 |
// 手中无货但可以买入

int main() {
  cin.sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  // 初始状态是f[1][2],处于可以买的状态
  // 其余状态非法设为负无穷
  f[0][0] = -INF, f[0][1] = -INF, f[0][2] = 0;
  // 状态转移
  for (int i = 1; i <= n; i++) {
    f[i][0] = max(f[i - 1][0], f[i - 1][2] - a[i]);
    f[i][1] = f[i - 1][0] + a[i];
    f[i][2] = max(f[i - 1][1], f[i - 1][2]);
  }
  // 最后的结果要么是刚刚买了，在冷冻期内，要么处于可以买的状态
  // 假如全部单调递减的话不买的收益是0，买了显然不符合常识
  cout << max(f[n][1], f[n][2]) << endl;
  return 0;
}
