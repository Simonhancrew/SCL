#include <algorithm>
#include <cstring>
#include <iostream>

/*
    状态机 + 树形dp
    要求每个点都能被观察到，当前节点存在三种情况，被父节点观察到，被子节点观察到，自己就放置节点
    f[i][0] 第i个结点的父结点被选
    f[i][1] 第i个结点有一个子节点被选
    f[i][2] 第i个节点本身被选
    属性是最终的所选代价最小
    f[u][0] += min(f[v][1],f[v][2])
    f[u][1] = min(w[k] + f[k][2] + sum(min(f[j][1],f[j][2]))) j != k
    f[u][2] += min(f[v][1],f[v][2],f[v][0]);
*/

using namespace std;

#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1510;

int n;
int e[N], ne[N], h[N], w[N], idx;
bool st[N];
int f[N][3];

void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

void dfs(int u) {
  f[u][2] = w[u];

  int sum = 0;
  for (int i = h[u]; i != -1; i = ne[i]) {
    int j = e[i];
    dfs(j);
    f[u][0] += min(f[j][1], f[j][2]);
    f[u][2] += min(min(f[j][0], f[j][1]), f[j][2]);
    sum += min(f[j][1], f[j][2]);
  }
  f[u][1] = 1e9;
  for (int i = h[u]; i != -1; i = ne[i]) {
    int j = e[i];
    f[u][1] = min(f[u][1], sum - min(f[j][1], f[j][2]) + f[j][2]);
  }
}

int main() {
  fast_cin();
  cin >> n;
  memset(h, -1, sizeof h);
  for (int i = 0; i < n; i++) {
    int id, cost, cnt;
    cin >> id >> cost >> cnt;
    w[id] = cost;
    while (cnt--) {
      int m;
      cin >> m;
      add(id, m);
      st[m] = true;
    }
  }
  int root = 1;
  while (st[root]) root++;
  dfs(root);
  cout << min(f[root][1], f[root][2]) << endl;
  return 0;
}