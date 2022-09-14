#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e3 + 10, M = 1e6 + 10;

/*
    最短路模型的问题，将判重数据多开，记录前置节点
    最后按照路径搜索一次全部
*/

typedef pair<int, int> PII;
#define x first
#define y second

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int n;
int g[N][N];
PII q[M];
PII pre[N][N];  // 将st变为记录一个前节点的数组

void bfs(int x, int y) {
  int hh = 0, tt = 0;
  q[0] = {x, y};
  memset(pre, -1, sizeof pre);
  pre[x][y] = {0, 0};
  while (hh <= tt) {
    PII t = q[hh++];
    for (int i = 0; i < 4; i++) {
      int nx = t.x + dx[i], ny = t.y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
      if (g[nx][ny]) continue;
      if (pre[nx][ny].x != -1) continue;
      pre[nx][ny] = t;
      q[++tt] = {nx, ny};
    }
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> g[i][j];
    }
  }
  bfs(n - 1, n - 1);
  PII end = {0, 0};
  while (true) {
    cout << end.x << ' ' << end.y << endl;
    if (end.x == n - 1 && end.y == n - 1) break;
    end = pre[end.x][end.y];
  }
  return 0;
}
