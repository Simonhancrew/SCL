#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e4 + 10;
int n;
int f[N];

// 贪心 + 01背包
// 确定吃的顺序，先i再j话，基础能量和是一样的，损失是s[i] * l[j]
// 反之的话，s[j] * l[i],损失越小越好，则可以推断出来一个排序的依据
// 在这个小集合里面按照顺序选就可以了
// 选法就是一个简答的01背包

struct stone {
  int s, e, l;
} stone[N];

int main() {
  int t;
  cin >> t;
  for (int ca = 1; ca <= t; ca++) {
    cin >> n;
    int m = 0;
    for (int i = 0; i < n; i++) {
      int s, l, e;
      cin >> s >> e >> l;
      stone[i].s = s, stone[i].e = e, stone[i].l = l;
      m += s;
    }
    sort(stone, stone + n,
         [](auto &lhs, auto &rhs) { return lhs.s * rhs.l < lhs.l * rhs.s; });
    memset(f, -0x3f, sizeof f);
    f[0] = 0;
    for (int i = 0; i < n; i++) {
      int s = stone[i].s, e = stone[i].e, l = stone[i].l;
      for (int j = m; j >= s; j--) {
        f[j] = max(f[j],
                   f[j - s] + max(0, e - (j - s) * l));  // 石头的能量不会是负数
      }
    }
    int res = -1;
    for (int i = 0; i <= m; i++) res = max(res, f[i]);
    printf("Case #%d: %d\n", ca, res);
  }
  return 0;
}