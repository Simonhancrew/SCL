#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 20, M = 1 << 12, mod = 1e8;

int n, m;
int a[N];
int f[N][M];           // 前i行，最后一行的拜访状态是j
vector<int> st;        // 合法的状态集合
vector<int> trans[M];  // 合法状态的转移，注意是idx到idx的转移

bool check(int u) {
  for (int i = 0; i + 1 < m; i++)
    if ((u >> i & 1) && (u >> i + 1 & 1)) return false;
  return true;
}

int main() {
  cin.sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++) {
      int t;
      cin >> t;
      a[i] += (!t) << j;  // 不合适种植的部分设置为1
    }
  }

  for (int a = 0; a < 1 << m; a++) {
    if (check(a)) st.push_back(a);
  }

  for (int i = 0; i < st.size(); i++) {
    for (int j = 0; j < st.size(); j++) {
      int a = st[i], b = st[j];
      if (!(a & b)) {
        trans[i].push_back(j);
      }
    }
  }

  f[0][0] = 1;
  // 多开一行，最后结果关注最后一行不放的情况
  for (int i = 1; i <= n + 1; i++) {
    for (int j = 0; j < st.size(); j++) {
      if (st[j] & a[i])
        continue;  // 不必考虑f[i - 1][k]，i-1行状态k是否和a[i -
                   // 1]重复，递推的关系，此处会忽略
      for (auto k :
           trans[j]) {  // 之前的状态k如果和a[i - 1]冲突的话f[i - 1][k]会是0
        f[i][j] = (f[i - 1][k] + f[i][j]) % mod;
      }
    }
  }
  cout << f[n + 1][0] << endl;
  return 0;
}
