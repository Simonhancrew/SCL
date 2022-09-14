#include <iostream>

using namespace std;

/*
    f[i]是点燃烽火台i的花费，只要前面[i - m,i -
   1]的烽火台是点燃的就可以将信号传递 f[i] = min(f[j]) + a[i],其中j在范围[i -
   m,i - 1]中，区间最小值可以用单调队列来维护 最后取输出的时候，同样只要[n - m +
   1,n]这个区间的是点燃的就可以传递到信号，取这个区间的最小花费就可以了
*/

#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)

const int N = 2e5 + 10, INF = 0x3f3f3f3f;

int n, m;
int a[N], q[N];
int f[N];

int main() {
  fast_cin();
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  int hh = 0, tt = 0;
  for (int i = 1; i <= n; i++) {
    if (hh <= tt && q[hh] < i - m) hh++;
    f[i] = f[q[hh]] + a[i];
    while (hh <= tt && f[q[tt]] >= f[i]) tt--;
    q[++tt] = i;
  }
  int res = INF;
  for (int i = n - m + 1; i <= n; i++) res = min(res, f[i]);
  cout << res << endl;
  return 0;
}