#include <iostream>

using namespace std;

const int N = 1e5 + 10;
typedef long long LL;
#define fast_cin()             \
  ios::sync_with_stdio(false); \
  cin.tie(0);                  \
  cout.tie(0)

/*
    区间增减不难想到差分，即通过+1，-1让[b2,bn]全部变成0
    最快的一个方法就是贪心的让[l,r]区间的左右两边一个是正数，一个是
    复数，这样加减抵消是最快的
    因为最后正负数的绝对值可能是不同的，所以剩余的数可以通过和b[1] || b[n + 1]
    配对来完成剩下的变0
    最后的次数就可以看作最后匹配的方案选择给b[1]的问题
*/

int n;
int a[N], b[N];

int main() {
  fast_cin();
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) b[i] = a[i] - a[i - 1];
  LL p = 0, q = 0;
  for (int i = 2; i <= n; i++) {
    if (b[i] > 0)
      p += b[i];
    else
      q -= b[i];
  }
  cout << max(p, q) << endl;
  cout << abs(p - q) + 1 << endl;
  return 0;
}
