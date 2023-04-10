#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int stk[N], tt;
int a[N];

#if 1

// 正向的思路, 从左到右遍历, 遍历当前节点的时候，找到上一个更小

int main() {
  int n;
  cin.sync_with_stdio(false);
  cin >> n;
  for (int i = 0; i <= n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) {
    int x = a[i];
    while (tt && stk[tt] >= x) tt--;
    if (tt)
      cout << stk[tt] << ' ';
    else
      cout << -1 << ' ';
    stk[++tt] = x;
  }
  return 0;
}

#else 

// 从右往左的思路, 遍历到当前节点的时候，看看当前节点可以做右边那些节点的上一个更小

int ans[N];
int idx;

int main() {
  ios::sync_with_stdio(false);
  cout.tie(nullptr);
  cin >> n;
  for (int i = 0;i < n;i++) cin >> a[i];
  idx = -1;
  memset(ans, -1, sizeof ans);
  for (int i = n - 1;i >= 0;i--) {
    while (idx != -1 && a[stk[idx]] > a[i]) {
      ans[stk[idx--]] = a[i];
    }
    stk[++idx] = i;
  }
  for (int i = 0; i < n;i++) cout << ans[i] << ' ';
  cout << '\n';
}


#endif
