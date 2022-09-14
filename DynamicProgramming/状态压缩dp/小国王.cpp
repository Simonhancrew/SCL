#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 15, M = 1100, K = 110;

typedef long long LL;

int n, m;
vector<int> st;        // 合法状态记录
vector<int> trans[M];  // 可以相互转移的状态
int cnt[M];            // 每个状态多少个1
LL f[N][K][M];

bool check(int a) {
  for (int i = 0; i < n; i++) {
    if ((a >> i & 1) && (a >> i + 1 & 1)) {
      return false;
    }
  }
  return true;
}

int count(int a) {
  int res = 0;
  while (a) {
    if (a & 1) res++;
    a >>= 1;
  }
  return res;
}

int main() {
  cin >> n >> m;
  // 预处理合法状态,没有连续的1
  for (int i = 0; i < 1 << n; i++) {
    if (check(i)) {
      st.push_back(i);
      cnt[i] = count(i);  // 当前状态有多少个1
    }
  }
  // 这些状态中那些可以合法转移，既a & b == 0 && a | b 没有连续的1
  for (int i = 0; i < st.size(); i++) {
    for (int j = 0; j < st.size(); j++) {
      int a = st[i], b = st[j];
      if ((a & b) == 0 && check(a | b)) {
        trans[i].push_back(j);
      }
    }
  }
  f[0][0][0] = 1;  // 期盼外，合法方案唯一
  for (int i = 1; i <= n + 1; i++) {
    for (int j = 0; j <= m; j++) {
      for (int a = 0; a < st.size(); a++) {
        for (auto b : trans[a]) {
          int c = cnt[st[a]];
          if (j >= c) {
            f[i][j][a] += f[i - 1][j - c][b];
          }
        }
      }
    }
  }
  cout << f[n + 1][m][0] << endl;
  return 0;
}