#include <iostream>
#include <vector>
// #include <algorithm>
#include <numeric>
#include <array>

using namespace std;

// from lc 1775, 让两个数组的和的最小的改动次数
// 不难想到双向的奔赴是最优秀的计数解
// 首先计算sum之差，然后把sum更大的那个数组变小，sum更小的那个数组变大
// 贪心的考虑，将小的数组中的值都变6，大的数组中的值都变1。为了避免每次只考虑一个diff
// 把diff值记录成map，比如6->1, diff = 5, cnt[5]++, 这样就能在找diff的时候计算多个
// 倒序遍历，直到两个数组相等

const int N = 1e5 + 10;

int n, m;
vector<int> nums1, nums2;

void solve() {
  if (6 * n < m || 6 * m < n) {
    return;
  }
  int d = accumulate(nums1.begin(), nums1.end(), 0) - accumulate(nums2.begin(), nums2.end(), 0);
  if (d < 0) {
    d = -d;
    swap(nums1, nums2);
  }
  array<int, 6> cnt{};
  for (auto& x : nums1) {
    cnt[x - 1]++;
  }
  for (auto& x : nums2) {
    cnt[6 - x]++;
  }
  int ans = 0;
  for (int i = 5;i > 0;i--) {
    if (d - cnt[i] * i <= 0) {
      cout << ans + (d + i - 1) / i << endl;
      return;
    }
    d -= cnt[i] * i;
    ans += cnt[i];
  }
  // 合法的话不会执行到
  cout << ans << endl;
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  nums1.resize(n), nums2.resize(m);
  for(int i = 0;i < n;i++) cin >> nums1[i];
  for(int i = 0;i < m;i++) cin >> nums2[i];
  solve();
  return 0;
}

