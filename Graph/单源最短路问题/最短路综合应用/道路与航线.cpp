#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
    可以看作双向链接集合块被单向连接的边互连，对外部做topsort，对内部做dij就可以求得最短路了

    1. 首先输入双向边，然后flood fill找到具体的连通块数量和每个连通块里的点集
    2. 然后输入航道，计算入度
    3.
   按照top序处理每个集合块，然后在集合内部做dij，需要注意的是不知道具体的大小
    需要将所有的点都放进堆中
    4. 遍历内部点的过程中，如果发现id[node] != id[cur]，且in[id[cur]] ==
   0了，则将这个连通块 id放进队列中做topsort
*/

#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)
typedef pair<int, int> PII;
const int N = 25010, M = 150010, INF = 0x3f3f3f3f;

int n, mr, mp, s;
int e[M], ne[M], w[M], h[N], idx;
int dist[N], id[N], in[N];
int bcnt;
bool st[N];
vector<int> blk[N];
queue<int> q;

void add(int a, int b, int c) {
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dfs(int u, int bid) {
  id[u] = bid, blk[bid].push_back(u);

  for (int i = h[u]; i != -1; i = ne[i]) {
    int j = e[i];
    if (id[j]) continue;
    dfs(j, bid);
  }
}

void dijstra(int bid) {
  priority_queue<PII, vector<PII>, greater<PII>> heap;
  for (auto t : blk[bid]) heap.push({dist[t], t});
  while (heap.size()) {
    auto t = heap.top();
    heap.pop();
    int node = t.second;

    if (st[node]) continue;
    st[node] = true;

    for (int i = h[node]; i != -1; i = ne[i]) {
      int j = e[i];
      if (id[j] != id[node] && --in[id[j]] == 0) q.push(id[j]);
      if (dist[j] > dist[node] + w[i]) {
        dist[j] = dist[node] + w[i];
        if (id[j] == id[node]) heap.push({dist[j], j});
      }
    }
  }
}

void topsort() {
  memset(dist, 0x3f, sizeof dist);
  dist[s] = 0;
  for (int i = 1; i <= bcnt; i++) {
    if (!in[i]) q.push(i);
  }
  while (q.size()) {
    auto t = q.front();
    q.pop();
    dijstra(t);
  }
}

int main() {
  fast_cin();
  cin >> n >> mr >> mp >> s;

  memset(h, -1, sizeof h);
  while (mr--) {
    int a, b, c;
    cin >> a >> b >> c;
    add(a, b, c), add(b, a, c);
  }

  for (int i = 1; i <= n; i++) {
    if (!id[i]) {
      dfs(i, ++bcnt);
    }
  }

  while (mp--) {
    int a, b, c;
    cin >> a >> b >> c;
    add(a, b, c);
    in[id[b]]++;
  }

  topsort();

  for (int i = 1; i <= n; i++) {
    if (dist[i] >= INF / 2)
      cout << "NO PATH" << endl;
    else
      cout << dist[i] << endl;
  }
  return 0;
}
