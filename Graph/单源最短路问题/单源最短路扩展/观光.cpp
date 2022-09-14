#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

// Created by Simonhancrew on 2022/04/14

using namespace std;

/*
    求一个最短路和一个次短路的方案数。
    最短路很好求，主要思考如何求次短路的方案数。
    因为需要确定一个拓扑序查找，考虑dij，随后在更新过程中多维护一个次短路
    因为边权都是大于0的，所有不存在环形依赖，所以次短路的更新也是拓扑序的
    即更新某个点的时候他的依赖值一定是完全被更新的
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e3 + 10, M = 1e4 + 10;

struct Node {
  int id, type, dist;
  bool operator>(Node const &W) const { return dist > W.dist; }
};

int T, n, m, start, tail;
bool st[N][2];
int dist[N][2], cnt[N][2];
int h[N], e[M], ne[M], w[M], idx;

void add(int a, int b, int c) {
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int dijstra() {
  memset(dist, 0x3f, sizeof dist);
  memset(cnt, 0, sizeof cnt);
  memset(st, 0, sizeof st);

  dist[start][0] = 0, cnt[start][0] = 1;
  priority_queue<Node, vector<Node>, greater<Node>> heap;

  heap.push({start, 0, 0});
  while (heap.size()) {
    auto t = heap.top();
    heap.pop();
    int node = t.id, type = t.type, d = t.dist;
    int count = cnt[node][type];
    if (st[node][type]) continue;
    st[node][type] = true;
    for (int i = h[node]; i != -1; i = ne[i]) {
      int j = e[i];
      if (dist[j][0] > d + w[i]) {
        dist[j][1] = dist[j][0], cnt[j][1] = cnt[j][0];
        heap.push({j, 1, dist[j][1]});
        dist[j][0] = d + w[i], cnt[j][0] = count;
        heap.push({j, 0, dist[j][0]});
      } else if (dist[j][0] == d + w[i]) {
        cnt[j][0] += count;
      } else if (dist[j][1] > d + w[i]) {
        dist[j][1] = d + w[i], cnt[j][1] = count;
        heap.push({j, 1, dist[j][1]});
      } else if (dist[j][1] == d + w[i])
        cnt[j][1] += count;
    }
  }
  int res = cnt[tail][0];
  if (dist[tail][0] + 1 == dist[tail][1]) res += cnt[tail][1];
  return res;
}

int main() {
  fast_cin();
  cin >> T;
  while (T--) {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    idx = 0;

    while (m--) {
      int a, b, c;
      cin >> a >> b >> c;
      add(a, b, c);
    }

    cin >> start >> tail;

    cout << dijstra() << endl;
  }
  return 0;
}