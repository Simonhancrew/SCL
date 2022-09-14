#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 1e3 + 10;

/*
    适用于边权只有0和1的情况，利用双端队列模拟堆。
    0加到队头，1加到队尾
    同样在出队更新的时候判重，和dij一个思路
*/

typedef pair<int, int> PII;
#define x first
#define y second
#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)
int st[N][N], dist[N][N];
bool rec[N][N];
int n, sx, sy;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int bfs(int x, int y) {
  memset(dist, 0x3f, sizeof dist);
  deque<PII> heap;
  dist[x][y] = 0;
  heap.push_back({x, y});

  while (heap.size()) {
    auto t = heap.front();
    heap.pop_front();

    int a = t.x, b = t.y;
    if (st[a][b]) continue;
    st[a][b] = 1;

    for (int i = 0; i < 4; i++) {
      int nx = a + dx[i], ny = b + dy[i];
      if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
        int d = rec[nx][ny];
        if (dist[nx][ny] > dist[a][b] + d) {
          dist[nx][ny] = dist[a][b] + d;
          if (d)
            heap.push_back({nx, ny});
          else
            heap.push_front({nx, ny});
        }
      }
    }
  }
  return dist[0][0];
}

int main() {
  fast_cin();
  cin >> n >> sx >> sy;
  while (n--) {
    int l, r;
    cin >> l >> r;
    rec[l][r] = 1;
  }
  cout << bfs(sx, sy) << '\n';
  return 0;
}