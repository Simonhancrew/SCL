#include <iostream>

using namespace std;

const int N = 2e6 + 10;

/*
    当前点出发走到下一个点剩的油，P[i] - d[i] = s[i]
    如果某个区间[i,i + n - 1]是可达的话，这个区间的前缀和数组应该都是大于等于0的
    直接处理整个前缀和，最后将[i,i + n - 1]区间中的最小值减去s[i - 1],
    只要这个值 >= 0就是合法起点。顺时针，我要拿到i右边的最小值，自然是从右遍历的
    逆时针是一个镜像的过程
*/

typedef long long LL;
#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)
int n;
LL p[N], d[N];
LL s[N];
LL q[N];
bool ans[N];

int main() {
  fast_cin();
  cin >> n;
  // 顺时针
  /*
      拆环成链，2倍原数组
      [1,n]的数中选择一个作为起点，s[i],终点s[i + n - 1]
  */
  for (int i = 1; i <= n; i++) cin >> p[i] >> d[i];
  for (int i = 1; i <= n; i++) s[i] = s[i + n] = p[i] - d[i];
  for (int i = 1; i <= 2 * n; i++) s[i] += s[i - 1];
  int hh = 0, tt = -1;
  for (int i = 2 * n; i; i--) {
    if (hh <= tt && q[hh] >= i + n) ++hh;
    while (hh <= tt && s[q[tt]] >= s[i]) tt--;
    q[++tt] = i;
    if (i <= n) {
      if (s[q[hh]] - s[i - 1] >= 0) ans[i] = true;
    }
  }
  // 逆时针，方向是从右到左的，处理一个后缀数组。出发的起点在[n + 1,2 * n]中
  hh = 0, tt = -1;
  d[0] = d[n];
  for (int i = 1; i <= n; i++) s[i] = s[i + n] = p[i] - d[i - 1];
  for (int i = 2 * n; i >= 1; i--) s[i] += s[i + 1];
  for (int i = 1; i <= 2 * n; i++) {
    if (hh <= tt && q[hh] <= i - n) hh++;
    while (hh <= tt && s[q[tt]] >= s[i]) tt--;
    q[++tt] = i;
    if (i >= n + 1) {
      if (s[q[hh]] >= s[i + 1]) ans[i - n] = true;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (ans[i])
      cout << "TAK" << '\n';
    else
      cout << "NIE" << '\n';
  }
  return 0;
}