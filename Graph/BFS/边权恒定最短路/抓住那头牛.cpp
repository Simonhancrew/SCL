#include <cstring>
#include <iostream>

using namespace std;

typedef pair<int, int> PII;
#define x first
#define y second

const int N = 1e5 + 10;

/*
    先减再乘最优
*/

int n, k;
int q[N];
int dist[N];

int bfs() {
  memset(dist, -1, sizeof dist);
  dist[n] = 0;
  q[0] = n;
  int hh = 0, tt = 0;
  while (hh <= tt) {
    int t = q[hh++];
    if (t == k) return dist[t];
    if (t + 1 < N && dist[t + 1] == -1) {
      dist[t + 1] = dist[t] + 1;
      q[++tt] = t + 1;
    }
    if (t - 1 >= 0 && dist[t - 1] == -1) {
      dist[t - 1] = dist[t] + 1;
      q[++tt] = t - 1;
    }
    if (t * 2 < N && dist[t * 2] == -1) {
      dist[t * 2] = dist[t] + 1;
      q[++tt] = t * 2;
    }
  }
  return -1;
}

int main() {
  cin >> n >> k;
  cout << bfs() << endl;
  return 0;
}