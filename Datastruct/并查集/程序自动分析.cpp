#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

const int N = 2e6 + 10;
#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)

/*
    离散化 + 并查集
    因为总的范围是1e9的，开等长的array基本狗带
    考虑离散化，这里的离散化不用保序，所以直接hash就可以了
*/

int t, n;
int cnt;
int p[N];
unordered_map<int, int> mp;

struct query {
  int a, b, e;
} query[N];

int get(int x) {
  if (mp.count(x) == 0) mp[x] = cnt++;
  return mp[x];
}

int find(int x) {
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}

int main() {
  fast_cin();
  cin >> t;
  while (t--) {
    cin >> n;
    cnt = 0, mp.clear();  // 记得复原mp和计数器
    for (int i = 0; i < n; i++) {
      int a, b, e;
      cin >> a >> b >> e;
      query[i] = {get(a), get(b), e};
    }
    for (int i = 0; i < cnt; i++) p[i] = i;
    for (int i = 0; i < n; i++) {
      if (query[i].e == 1) {
        int pa = find(query[i].a), pb = find(query[i].b);
        p[pa] = pb;
      }
    }
    bool flag = true;
    for (int i = 0; i < n; i++) {
      if (query[i].e == 0) {
        int pa = find(query[i].a), pb = find(query[i].b);
        if (pa == pb) {
          flag = false;
          break;
        }
      }
    }
    if (flag)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}