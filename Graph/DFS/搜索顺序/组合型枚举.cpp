#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 30;

int m, n;
int path[N];

// 保证顺序枚举
void dfs(int start, int cnt) {
  if (cnt == m) {
    for (int i = 0; i < m; i++) cout << path[i] << ' ';
    cout << endl;
  } else {
    for (int i = start; i <= n; i++) {
      path[cnt] = i;
      dfs(i + 1, cnt + 1);
      path[cnt] = 0;
    }
  }
}

int main() {
  cin >> n >> m;
  dfs(1, 0);
  return 0;
}