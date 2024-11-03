#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

// 多一维度记录多的要求就行了

const int N = 1e2 + 10;
int dp[N][N];
int n, V, M;

int main() {
  cin >> n >> V >> M;
  int v, m, w;
  for (int i = 0; i < n; i++) {
    cin >> v >> m >> w;
    for (int j = V; j >= v; j--) {
      for (int k = M; k >= m; k--) {
        dp[j][k] = max(dp[j][k], dp[j - v][k - m] + w);
      }
    }
  }
  cout << dp[V][M] << endl;
}