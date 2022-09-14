#include <iostream>

using namespace std;

const int N = 1e4 + 10;

/*
    01背包 + 并查集
    看似一个有依赖的背包问题，实际上所有的依赖高度相关
    完全可以打包所有的依赖项之后做
    可以用并查集讲所有的依赖关系合并之后做一个01背包
*/

int n, m, w;
int p[N], v[N], r[N];  // 并查集，价钱，价值
int f[N];

int find(int x) {
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}

int main() {
  cin >> n >> m >> w;
  for (int i = 0; i < n; i++) {
    cin >> v[i] >> r[i];
    p[i] = i;
  }
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;  // 物品下标从1开始的
    int pa = find(a), pb = find(b);
    if (pa == pb) continue;
    p[pa] = pb, v[pb] += v[pa], r[pb] += r[pa];  // 合并
  }
  for (int i = 0; i < n; i++) {
    if (p[i] == i) {
      for (int j = w; j >= v[i]; j--) {
        f[j] = max(f[j], f[j - v[i]] + r[i]);
      }
    }
  }
  cout << f[w] << endl;
  return 0;
}