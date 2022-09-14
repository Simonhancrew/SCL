#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/03

using namespace std;

/*
    看成一个树，然后递推的从后往前找，也就是要从树的叶子节点往前找
    针对每个后缀看看有没有前缀是匹配的就行了，直接利用ne往前找就行了
    递加的添加道前面的节点就行了
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1e6 + 10;

int n;
char s[N];
int tr[N][26], ne[N], idx;
int q[N], f[N];
int id[210];

void insert(int x) {
  int p = 0;
  for (int i = 0; s[i]; i++) {
    int t = s[i] - 'a';
    if (!tr[p][t]) tr[p][t] = ++idx;
    p = tr[p][t];
    f[p]++;  // 当前节点有
  }
  id[x] = p;
}

void build() {
  int hh = 0, tt = -1;
  for (int i = 0; i < 26; i++) {
    if (tr[0][i]) q[++tt] = tr[0][i];
  }
  while (hh <= tt) {
    int t = q[hh++];
    for (int i = 0; i < 26; i++) {
      int p = tr[t][i];
      if (!p)
        tr[t][i] = tr[ne[t]][i];
      else {
        ne[p] = tr[ne[t]][i];
        q[++tt] = p;
      }
    }
  }
}

int main() {
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s;
    insert(i);
  }
  build();
  for (int i = idx - 1; i >= 0; i--) f[ne[q[i]]] += f[q[i]];
  for (int i = 0; i < n; i++) cout << f[id[i]] << endl;
  return 0;
}