#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/06/30

using namespace std;

/*
    首先将棋盘按照坐标和的奇偶性分成两部分（这样就能用二分图的算法做），然后跳日字形的话
    跳完之后奇偶性是变化的。
    这里互相不能攻击骑士数量等价于找一个最大独立集。将能相互攻击到的骑士看作链接了一条边
    因此做一个最大匹配，减去坏点和最大匹配数就是最大独立及的数量
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                                                             \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr);                                                            \
  cout.tie(nullptr)

#define x first
#define y second

const int INF = 0x3f3f3f3f, N = 110;

int n, m, t;
bool g[N][N], st[N][N];
PII match[N][N];

int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool find(int x, int y) {
  for (int i = 0; i < 8; i++) {
    int nx = x + dx[i], ny = y + dy[i];
    if (nx <= 0 || nx > n || ny <= 0 || ny > m)
      continue;
    if (g[nx][ny])
      continue;
    if (st[nx][ny])
      continue;
    st[nx][ny] = true;
    auto t = match[nx][ny];
    if (t.x == 0 || find(t.x, t.y)) {
      match[nx][ny] = {x, y};
      return true;
    }
  }
  return false;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m >> t;
  for (int i = 0; i < t; i++) {
    int x, y;
    cin >> x >> y;
    g[x][y] = true;
  }

  int res = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if ((i + j) % 2 && !g[i][j]) {
        memset(st, 0, sizeof st);
        if (find(i, j))
          res++;
      }
    }
  }
  cout << n * m - t - res << endl;
  return 0;
}