#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e3 + 10, M = N * N;

// 多源BFS的典型问题就是给定两个岛屿，求最短的连接距离
// 其中求岛屿可以用flood fill去做

// BFS求最短路的时候，对头的一定是一个最小值，具有单调性(队列中的值)
// 所以只要初始化全-1就可以
// 针对多源BFS，只要将初始的起点dist都设为0，放入队列中做一次更新就可以了

// 为什么多源BFS是对的，因为队列先进先出，队头的dist永远可以保证是比较小的。
// 如果用dist小的队头更新到了另一个岛屿（矩阵），这个距离一定是最小的。
// 其中需要保证的就是权值恒定，这也是BFS做最短路问题需要保证的。

typedef pair<int, int> PII;
#define x first
#define y second
#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)

int n, m;
char g[N][N];
int dist[N][N];
PII q[M];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

void bfs() {
  int hh = 0, tt = -1;
  memset(dist, -1, sizeof dist);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == '1') {
        q[++tt]    = {i, j};
        dist[i][j] = 0;
      }
    }
  }
  while (hh <= tt) {
    PII t = q[hh++];
    for (int i = 0; i < 4; i++) {
      int nx = t.x + dx[i], ny = t.y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m)
        continue;
      if (dist[nx][ny] != -1)
        continue;
      dist[nx][ny] = dist[t.x][t.y] + 1;
      q[++tt]      = {nx, ny};
    }
  }
}

int main() {
  fast_cin();
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    cin >> g[i];
  bfs();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << dist[i][j] << ' ';
    }
    cout << '\n';
  }
  return 0;
}