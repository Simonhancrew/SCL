#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/02/25

using namespace std;

/*
    简单的讲就是在trie上做kmp
*/

#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1e4 + 10, M = 1e6 + 10, S = 55;

int t, n;
int cnt[N * S], idx;
int tr[N * S][26];
char str[M];
int q[N * S], ne[N * S];

void insert() {
  int p = 0;
  for (int i = 0; str[i]; i++) {
    int t = str[i] - 'a';
    if (!tr[p][t]) tr[p][t] = ++idx;
    p = tr[p][t];
  }
  cnt[p]++;
}

/*
    一个BFS的建立过程
*/
void build() {
  int hh = 0, tt = -1;
  for (int i = 0; i < 26; i++) {
    if (tr[0][i]) q[++tt] = tr[0][i];
  }
  while (hh <= tt) {
    int t = q[hh++];
    for (int i = 0; i < 26; i++) {
      int c = tr[t][i];
      if (!c) continue;
      int j = ne[t];
      while (j && !tr[j][i]) j = ne[j];
      if (tr[j][i]) j = tr[j][i];
      ne[c] = j;
      q[++tt] = c;
    }
  }
}

#ifdef TrieMap
/*
    trie图的构建方式,匹配失败的话，一步到位
*/
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
#endif

int main() {
  fast_cin();
  cin >> t;
  while (t--) {
    memset(tr, 0, sizeof tr);
    memset(cnt, 0, sizeof cnt);
    memset(ne, 0, sizeof ne);
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> str;
      insert();
    }

    build();

    cin >> str;
    int res = 0;
    for (int i = 0, j = 0; str[i]; i++) {
      int t = str[i] - 'a';
      while (j && !tr[j][t]) j = ne[j];
      if (tr[j][t]) j = tr[j][t];
      int p = j;
      while (p) {
        res += cnt[p];
        cnt[p] = 0;
        p = ne[p];
      }
    }
#ifdef TrieMap
    for (int i = 0, j = 0; str[i]; i++) {
      int t = str[i] - 'a';
      j = tr[j][t];
      int p = j;
      while (p) {
        res += cnt[p];
        cnt[p] = 0;
        p = ne[p];
      }
    }
#endif
    cout << res << endl;
  }
  return 0;
}