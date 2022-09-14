#include <iostream>
#include <queue>

using namespace std;

const int N = 55;

/*
    在flood fill中顺便完成区域大小统计
*/

typedef pair<int, int> PII;
#define x first
#define y second

int st[N][N], g[N][N];
int n, m;
int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};

int bfs(int x, int y) {
  queue<PII> q;
  q.push({x, y});
  st[x][y] = 1;
  int area = 0;
  while (q.size()) {
    area++;
    auto t = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int nx = t.x + dx[i], ny = t.y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny > m) continue;
      if (st[nx][ny]) continue;
      if (g[t.x][t.y] >> i & 1) continue;
      st[nx][ny] = 1;
      q.push({nx, ny});
    }
  }
  return area;
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> g[i][j];
    }
  }
  int cnt = 0, area = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!st[i][j]) {
        area = max(area, bfs(i, j));
        cnt++;
      }
    }
  }
  cout << cnt << endl;
  cout << area << endl;
}