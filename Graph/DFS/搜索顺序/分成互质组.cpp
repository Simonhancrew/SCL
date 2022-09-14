#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 11;

/*
    优先把某个数加到最后一个组，不行就新开一组
*/

int n, ans;
int w[N];
int group[N][N];
bool st[N];

int gcd(int a, int b)  // 欧几里得算法
{
  return b ? gcd(b, a % b) : a;
}

bool check(int g[], int rhs, int idx) {
  for (int i = 0; i < rhs; i++) {
    if (gcd(w[g[i]], w[idx]) > 1) return false;
  }
  return true;
}

// group,当前group大小，全局用了多少数，防止重复，当前可以枚举的数的起点
// 比如，1，2，3和3，2，1其实是一个方案
void dfs(int g, int gc, int tc, int start) {
  if (g >= ans) return;
  if (tc == n) {
    ans = g;
    return;
  }
  bool flag = true;
  for (int i = start; i < n; i++) {
    if (!st[i] && check(group[g], gc, i)) {
      st[i] = true;
      group[g][gc] = i;
      dfs(g, gc + 1, tc + 1, i + 1);
      st[i] = false;
      flag = false;
    }
  }
  if (flag) dfs(g + 1, 0, tc, 0);
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> w[i];
  ans = 20;
  dfs(1, 0, 0, 0);
  cout << ans << endl;
  return 0;
}