#include <algorithm>
#include <iostream>

using namespace std;

#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)

const int N = 1e5 + 10;

/*
    这类平均值最大问题一般都是2分的（还有事最大值最小）
    这里快速的处理一段区间的平均值，利用前缀和，只要原数组a每个减去avg
    最后s的[l,r]区间和还大于等于0就表明这个平均值是可行的，可以继续扩大
    反之就需要缩减（一个二段性就出现了）
*/

int n, f;
double a[N], s[N];
double eps = 1e-5;

bool check(double avg) {
  double mini = 0;
  for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i] - avg;
  for (int i = f; i <= n; i++) {
    mini = min(mini, s[i - f]);
    if (s[i] - mini >= 0) return true;
  }
  return false;
}

int main() {
  fast_cin();
  cin >> n >> f;
  double l = 0, r = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    r = max(r, a[i]);
  }
  while (r - l > eps) {
    double mid = (r + l) / 2;
    if (check(mid))
      l = mid;
    else
      r = mid;
  }
  cout << int(r * 1000) << endl;
  return 0;
}