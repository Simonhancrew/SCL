#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 110;

// 首先这种依赖是树形的，直接考虑到树形dp
// 其次，dp[u][j]表示成以u为根节点，体积为j的情况下的最大获得价值
// 如果单纯的枚举u下所有的情况的话，一个2的指数级别复杂度
// 考虑之前的金明的预算方案里，这里直接按照体积划分
// 然后就退化成了一个分组背包，考虑其儿子节点的各类体积下的最佳方案
// coding中要预留根节点的空间去做dp
// 最后还要去除体积比根节点都小的情况（因为此时是无法选中的，后面能选，但是其实在根节点就被过滤了）

int dp[N][N];
int h[N], e[N], ne[N], idx;
int v[N], w[N];
int n, m;

void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

void dfs(int u) {
  for (int i = h[u]; i != -1; i = ne[i]) {  // 当前附加物品
    int son = e[i];
    dfs(son);
    for (int j = m - v[u]; j >= 0; j--) {  // 当前体积,记得预留根节点的空间
      for (int k = 0; k <= j; k++) {  // 枚举体积方案
        dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[son][k]);
      }
    }
  }
  // 将根节点加进去
  for (int i = m; i >= v[u]; i--) dp[u][i] = dp[u][i - v[u]] + w[u];
  for (int i = 0; i < v[u]; i++) dp[u][i] = 0;
}

int main() {
  cin >> n >> m;
  int root;
  memset(h, -1, sizeof h);
  for (int i = 1; i <= n; i++) {
    int p;
    cin >> v[i] >> w[i] >> p;
    if (p == -1)
      root = i;
    else
      add(p, i);
  }
  dfs(root);
  cout << dp[root][m] << endl;
  return 0;
}