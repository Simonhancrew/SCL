#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/05/08

using namespace std;

/*
    求一个最小值，等价于做一个最大路，所以替换所有的不等式为
    x[j]>=x[i] + w,连接i->j一个w的权值。
    因为保证所有的有糖，等价于所有的x[i] >= 1
    需要一个超级源点能走到所的边,此时可以转化x[i] >= x[0] + 1
    随后spfa求一个最长路，并找环
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10, M = 3e5 + 10;

int n, k;
int h[N], e[M], ne[M], w[M], idx;
LL dist[N], q[N], cnt[N];
bool st[N];

void add(int a, int b, int c) {
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

/*
    单独针对spfa找环的一个优化，用栈代替队列。这样在搜索的时候
    等价一个深搜，有环的话很快会找到。但最短路的话会稍慢
*/
bool spfa() {
  memset(cnt, 0, sizeof cnt);
  memset(st, 0, sizeof st);
  memset(dist, -0x3f, sizeof dist);
  dist[0] = 0;
  int hh = 0, tt = 0;
  q[++tt] = 0;
  while (hh != tt) {
    int t = q[tt--];
    st[t] = false;
    for (int i = h[t]; i != -1; i = ne[i]) {
      int j = e[i];
      if (dist[j] < dist[t] + w[i]) {
        dist[j] = dist[t] + w[i];
        cnt[j] = cnt[t] + 1;
        if (cnt[j] >= n + 1) return true;
        if (!st[j]) {
          st[j] = true;
          q[++tt] = j;
        }
      }
    }
  }
  return false;
}

int main() {
  fast_cin();
  memset(h, -1, sizeof h);
  cin >> n >> k;
  for (int i = 0; i < k; i++) {
    int x, a, b;
    cin >> x >> a >> b;
    if (x == 1)
      add(a, b, 0), add(b, a, 0);
    else if (x == 2)
      add(a, b, 1);
    else if (x == 3)
      add(b, a, 0);
    else if (x == 4)
      add(b, a, 1);
    else
      add(a, b, 0);
  }
  for (int i = 1; i <= n; i++) add(0, i, 1);
  if (spfa())
    cout << -1 << endl;
  else {
    LL res = 0;
    for (int i = 1; i <= n; i++) res += dist[i];
    cout << res << endl;
  }
  return 0;
}