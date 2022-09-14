#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int M = 30010;

// 简单01背包选取就可以了

int dp[M];

int main() {
  int n, m;
  cin >> m >> n;
  for (int i = 1; i <= n; i++) {
    int v, w;
    cin >> v >> w;
    w *= v;
    for (int j = m; j >= v; j--) {
      dp[j] = max(dp[j], dp[j - v] + w);
    }
  }
  cout << dp[m] << endl;
}