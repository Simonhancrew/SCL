#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2023/07/18

using namespace std;

// 因为染色会被覆盖，所以倒着做
// 并查集染色模型的经典题目，fa[i]是当前节点右边第一个没有被染色的节点
// 把并查集当树用，去找根，单方向，具有传递性，节点知道自己的根，然后到根了又重建新的根

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e6 + 10;

int n, m, p, q;
int fa[N], col[N];

int find(int x) {
  if (fa[x] != x) {
    fa[x] = find(fa[x]);
  }
  return fa[x];
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m >> p >> q;
  for (int i = 1; i <= n + 2; i++)
    fa[i] = i;
  for (int i = m; i > 0; i--) {
    int l = (i * p + q) % n + 1, r = (i * q + p) % n + 1;
    if (r < l)
      swap(r, l);
    while (find(l) <= r) {
      l      = find(l);
      col[l] = i;
      fa[l]  = l + 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    // 不要刷新缓冲区
    cout << col[i] << '\n';
  }
  return 0;
}
