#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

/*
    DFS判断是否联通
    系统压栈，注意判重
    不需要回溯，不是分支判断问题
*/

const int N = 110;

int T, n;
char g[N][N];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int sx, sy, tx, ty;
bool st[N][N];

bool dfs(int x, int y) {
  if (g[x][y] == '#') return false;
  if (x == tx && y == ty) return true;
  st[x][y] = true;
  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i], ny = y + dy[i];
    if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
    if (st[nx][ny]) continue;
    if (dfs(nx, ny)) return true;
  }
  return false;
}

int main() {
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> g[i];
    cin >> sx >> sy >> tx >> ty;
    memset(st, 0, sizeof st);
    if (dfs(sx, sy))
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}