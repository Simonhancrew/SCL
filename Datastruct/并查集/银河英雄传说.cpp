#include <iostream>

using namespace std;

#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)

const int N = 3e4 + 10;

/*
    判断是否一个集合比较简单，判断距离就需要多维护一些结构
    多维护一个到根的长度，记录每个集合的size大小
    每次合并a集合和b集合的时候，将a集合根到b集合根的距离设未size[pb]
    查询的时候做一个减法就可以了
*/

int p[N], d[N], cnt[N];
int t;

int find(int x) {
  if (p[x] != x) {
    int root = find(p[x]);
    d[x] += d[p[x]];
    p[x] = root;
  }
  return p[x];
}

int main() {
  fast_cin();
  for (int i = 0; i < N; i++) {
    p[i] = i;
    cnt[i] = 1;
  }
  cin >> t;
  while (t--) {
    char op;
    int a, b;
    cin >> op >> a >> b;
    if (op == 'M') {  // lazy update
      int pa = find(a), pb = find(b);
      if (pa == pb) continue;
      d[pa] = cnt[pb];
      cnt[pb] += cnt[pa];
      p[pa] = pb;
    } else {
      int pa = find(a), pb = find(b);
      if (pa != pb)
        cout << -1 << endl;
      else
        cout << max(0, abs(d[a] - d[b]) - 1) << endl;
    }
  }
  return 0;
}