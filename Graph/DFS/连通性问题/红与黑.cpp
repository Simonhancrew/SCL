#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 25;

/*
    DFS统计连通区域的点
*/

int m, n;
char g[N][N];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
bool st[N][N];
int sx, sy;

int dfs(int x, int y) {
  int cnt = 1;
  st[x][y] = 1;
  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i], ny = y + dy[i];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
    if (st[nx][ny] || g[nx][ny] == '#') continue;
    cnt += dfs(nx, ny);
  }
  return cnt;
}

int main() {
  while (cin >> m >> n, m || n) {
    for (int i = 0; i < n; i++) cin >> g[i];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (g[i][j] == '@') {
          sx = i, sy = j;
          break;
        }
      }
    }
    memset(st, 0, sizeof st);
    cout << dfs(sx, sy) << endl;
  }
  return 0;
}