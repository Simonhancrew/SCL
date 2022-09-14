#include <iostream>
#include <queue>

using namespace std;

/*
    做一遍经典的Flood Fill就可以了
*/

#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)

const int N = 1e3 + 10;

typedef pair<int, int> PII;
#define x first
#define y second

int n, m;
char g[N][N];
int st[N][N];

void bfs(int x, int y) {
  queue<PII> q;
  q.push({x, y});
  st[x][y] = 1;
  while (q.size()) {
    auto t = q.front();
    q.pop();
    for (int i = t.x - 1; i <= t.x + 1; i++) {
      for (int j = t.y - 1; j <= t.y + 1; j++) {
        if (i == t.x && j == t.y) continue;
        if (i < 0 | i >= n || j < 0 || j >= m) continue;
        if (g[i][j] == '.' || st[i][j] == 1) continue;
        st[i][j] = 1;
        q.push({i, j});
      }
    }
  }
}

// faster than bfs using std::queue
void dfs(int x, int y) {
  st[x][y] = 1;
  // 8 连通的处理方法
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if (i == x && j == y) continue;
      if (i < 0 | i >= n || j < 0 || j >= m) continue;
      if (g[i][j] == '.' || st[i][j] == 1) continue;
      dfs(i, j);
    }
  }
}

int main() {
  fast_cin();
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> g[i];
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == 'W' && !st[i][j]) {
        bfs(i, j);
        // dfs(i,j);
        cnt++;
      }
    }
  }
  cout << cnt << endl;
}