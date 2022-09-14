#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/07

using namespace std;

/*
    整个范围在int范围内，但是实际的间隔只有不到1e6
    这也引导去做一个化简。数论中很多关于质数的问题
    都可以做一个sqrt(n)的优化。
    考虑到每个合数n都可以由两个因子组成，一个最大因子d，另外一个就是n /
   d的一个质数 较小数是肯定<=sqrt(n)的，所以可以考虑做一个缩放
    先求出sqrt（n）范围内的质数，然后对更大的[l,r]范围内的合数做标记
    之后筛出[l,r]中的质数，最后做一个枚举
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e6 + 10;

int l, r;
int primes[N], cnt;
bool st[N];

void get_primes(int n) {
  memset(st, 0, sizeof st);
  cnt = 0;
  for (int i = 2; i <= n; i++) {
    if (!st[i]) primes[cnt++] = i;
    for (int j = 0; primes[j] <= n / i; j++) {
      st[primes[j] * i] = true;
      if (i % primes[j] == 0) break;
    }
  }
}

int main() {
  fast_cin();

  while (cin >> l >> r) {
    get_primes(int(5e5));

    memset(st, 0, sizeof st);
    for (int i = 0; i < cnt; i++) {
      LL p = primes[i];
      for (LL j = max(2 * p, (l + p - 1) / p * p); j <= r; j += p) {
        st[j - l] = true;
      }
    }
    cnt = 0;
    for (int i = 0; i <= r - l; i++) {
      if (!st[i] && i + l >= 2) {
        primes[cnt++] = i + l;
      }
    }

    if (cnt < 2)
      cout << "There are no adjacent primes." << endl;
    else {
      int minp = 0, maxp = 0;
      for (int i = 0; i + 1 < cnt; i++) {
        int d = primes[i + 1] - primes[i];
        if (d < primes[minp + 1] - primes[minp]) minp = i;
        if (d > primes[maxp + 1] - primes[maxp]) maxp = i;
      }
      cout << primes[minp] << ',' << primes[minp + 1];
      cout << " are closest, " << primes[maxp] << ',' << primes[maxp + 1];
      cout << " are most distant." << endl;
    }
  }
  return 0;
}