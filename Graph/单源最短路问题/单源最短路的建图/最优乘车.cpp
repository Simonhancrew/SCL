#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

// Created by Simonhancrew on 2022/03/25

using namespace std;

/*
    多集合跨越最小问题的建图和最短路求解

    要求出换车次数，同一趟车的所有车站都可以被连通
    此类问题可以建立一个边权恒为1的图，当前一趟车的全部节点互相连通
    且边权为1.之后针对每趟车，依然如此处理
    如果能直达的话，直接就能求出结果，是1。
    否则的话一定要换乘，找到最找的直达换乘车数
    最后-1即可。如果终点无法连通就是无解的
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 510;

int n, m;
bool g[N][N];
int d[N], q[N];
int sta[N];

void bfs() {
  memset(d, 0x3f, sizeof d);
  d[1] = 0;
  int hh = 0, tt = 0;
  q[0] = 1;
  while (hh <= tt) {
    auto t = q[hh++];
    for (int i = 1; i <= n; i++) {
      if (g[t][i] && d[i] == INF && d[i] > d[t] + 1) {
        d[i] = d[t] + 1;
        q[++tt] = i;
      }
    }
  }
}

int main() {
  fast_cin();
  cin >> m >> n;
  string line;
  getline(cin, line);
  for (int i = 0; i < m; i++) {
    getline(cin, line);
    stringstream ss(line);
    int cnt = 0, p;
    while (ss >> p) sta[cnt++] = p;
    for (int j = 0; j < cnt; j++) {
      for (int k = j + 1; k < cnt; k++) {
        g[sta[j]][sta[k]] = true;
      }
    }
  }
  bfs();
  if (d[n] == INF)
    cout << "NO" << endl;
  else
    cout << max(d[n] - 1, 0) << endl;
  return 0;
}