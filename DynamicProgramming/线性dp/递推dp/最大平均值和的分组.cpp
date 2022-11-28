#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2022/11/28

using namespace std;

// from LC 813

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

// f[i][j] 表示前i个数，分成j组，最大的平均数和
// f[i][j] = max(f[i][j], f[0..x][j - 1] + (s[i] - s[x]) / (i - x)), 其中x属于(0, i)
// 开始全部是-INF, f[0][0] = 0

int n, k;
vector<int> nums;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> k;
  nums.resize(n);
  for (int i = 0; i < n; i++)
    cin >> nums[i];
  vector<vector<double>> f(n + 1, vector<double>(k + 1, -1e9));
  vector<int> s(n + 1);
  for (int i = 1; i <= n; i++)
    s[i] = s[i - 1] + nums[i - 1];
  f[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      for (int q = 0; q < i; q++) {
        f[i][j] = max(f[i][j], f[q][j - 1] + (s[i] - s[q]) / (double)(i - q));
      }
    }
  }
  cout << f[n][k] << endl;
  return 0;
}