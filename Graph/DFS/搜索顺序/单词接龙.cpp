#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 22;

/*
    其实很像图论问题，先看每个单词能够连接那些单词
    最后爆搜连接的所有情乱
    因为还是内部搜索，每个点在当前分支的used更新之后，last是当前接的一个末尾
    在进入别的分支的时候需要还原成大分支顶部的原状态
*/

string s[N];
char start;
size_t n;
int used[N];
int g[N][N];
int ans;

void dfs(string tot, int last) {
  ans = max(ans, int(tot.size()));
  used[last]++;
  for (size_t i = 0; i < n; i++) {
    if (used[i] < 2 && g[last][i] >= 1) {
      dfs(tot + s[i].substr(g[last][i]), i);
    }
  }
  used[last]--;
}

int main() {
  cin >> n;
  for (size_t i = 0; i < n; i++) cin >> s[i];
  cin >> start;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      string a = s[i], b = s[j];
      for (int k = 1; k < min(a.size(), b.size()); k++) {
        if (a.substr(a.size() - k) == b.substr(0, k)) {
          g[i][j] = k;
          break;
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (start == s[i][0]) {
      dfs(s[i], i);  // 不要break
    }
  }
  cout << ans << endl;
  return 0;
}
