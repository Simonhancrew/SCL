#include <algorithm>
#include <cstring>
#include <iostream>


// Created by Simonhancrew on 2023/08/01

using namespace std;

// from lc 2681, 因为公式中只出现了最大最小值
// 而且是求子序列，所以可以先对数组排序，然后枚举最大最小值
// 换句话说，就是确定了最大值的时候，看这个点能怎么对全局做贡献
// 列举两个例子之后，看看能形成怎样的递推(这种一半都能形成递推)

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10, MOD = 1e9 + 7;

int nums[N];
int n;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 0;i < n;i++) {
    cin >> nums[i];
  }
  int ans = 0, s = 0;
  sort(nums, nums + n);
  for (int i = 0;i < n;i++) {
    ans = (ans + ((LL)nums[i] * nums[i]) % MOD * (s + nums[i])) % MOD;
    s = ((LL)s * 2 + nums[i]) % MOD;
  }
  cout << ans << endl;
  return 0;
}
