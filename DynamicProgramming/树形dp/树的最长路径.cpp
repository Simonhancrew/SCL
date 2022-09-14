#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1e4 + 10, M = 2 * N;
int e[M], ne[M], h[N], w[M], idx;
int n, a, b, c;
int ans;

void add(int a, int b, int c) {
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

/*
    每条路径上一定会有一个最高的节点，深搜每个节点，限制方向。
    f[u]表示当前搜索节点往下搜索的最长距离
    对于每个节点，找到他往下找的最长和次长路径，然后相加。
*/
int dfs(int u, int father) {
  int dist = 0;        // 往下搜索过程中最长路径
  int d1 = 0, d2 = 0;  // d1 = dist,d2是次长路径
  for (int i = h[u]; i != -1; i = ne[i]) {
    int j = e[i];
    if (j == father) continue;
    int d = dfs(j, u) + w[i];
    dist = max(dist, d);
    // 更新最长和次长
    if (d >= d1)
      d2 = d1, d1 = d;
    else if (d > d2)
      d2 = d;
  }
  ans = max(ans, d1 + d2);  // 结果就是每个节点的最长和次长的和
  return dist;
}

int main() {
  memset(h, -1, sizeof h);
  fast_cin();
  cin >> n;
  for (int i = 1; i < n; i++) {
    cin >> a >> b >> c;
    add(a, b, c), add(b, a, c);
  }
  dfs(1, -1);
  cout << ans << '\n';
  return 0;
}
