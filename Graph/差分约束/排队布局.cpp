#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/05/11

using namespace std;

/*
    这里要求一个1->n的最大距离，等价于求解一个最短路
    这里问能否有解就是做一个判负环（实质上已经有一个虚拟源点创建了）
    然后针对任意大的解就是在求最短路的过程中发现dist[n]是INF的
    求解的是一个最大值，即求一个上界的最小值。建立a <= b + 1的链
    到最后会形成一个不等式链，任意解就是1和n不联通的时候
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1010, M = 21010;

int n, m1, m2;
int h[N], e[M], ne[M], w[M], idx;
int dist[N], q[N], cnt[N];
bool st[N];

void add(int a, int b, int c) {
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool spfa(int size) {
  memset(cnt, 0, sizeof cnt);
  memset(dist, 0x3f, sizeof dist);
  memset(st, 0, sizeof st);
  int hh = 0, tt = 0;
  for (int i = 1; i <= size; i++) {
    q[tt++] = i;
    st[i] = true;
    dist[i] = 0;
  }
  while (hh != tt) {
    int t = q[hh++];
    if (hh == N) hh = 0;
    st[t] = false;
    for (int i = h[t]; i != -1; i = ne[i]) {
      int j = e[i];
      if (dist[j] > dist[t] + w[i]) {
        dist[j] = dist[t] + w[i];
        cnt[j] = cnt[t] + 1;
        if (cnt[j] >= n) return true;
        if (!st[j]) {
          st[j] = true;
          q[tt++] = j;
          if (tt == N) tt = 0;
        }
      }
    }
  }
  return false;
}

int main() {
  fast_cin();
  cin >> n >> m1 >> m2;
  memset(h, -1, sizeof h);
  for (int i = 1; i < n; i++) add(i + 1, i, 0);
  while (m1--) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a > b) swap(a, b);
    add(a, b, c);
  }
  while (m2--) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a > b) swap(a, b);
    add(b, a, -c);
  }
  if (spfa(n))
    cout << -1 << endl;
  else {
    spfa(1);
    if (dist[n] == INF)
      cout << -2 << endl;
    else
      cout << dist[n] << endl;
  }
  return 0;
}