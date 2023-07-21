#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

// Created by Simonhancrew on 2023/07/21

using namespace std;

// 求y1 + y2 + x2 - x1的最大值，其中给出的vecor<PII> ={{x, y}}
// 其中的x是递增的，且要求差值不大于x
// 发现只要y1 - x1尽可能大就行了，完全就是单调队列的模板题

int n, k;
vector<vector<int>> nums;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    nums.push_back({x, y});
  }
  deque<PII> q;
  int ans = INT_MIN;
  for (int r = 0; r < n; r++) {
    auto& cur = nums[r];
    while (q.size() && cur[0] - q.front().first > k) {
      q.pop_front();
    }
    auto diff = cur[1] - cur[0];
    if (!q.empty()) {
      ans = max(ans, cur[0] + cur[1] + q.front().second);
    }
    while (q.size() && q.back().second <= diff) {
      q.pop_back();
    }
    q.emplace_back(cur[0], diff);
  }
  cout << ans << endl;
  return 0;
}
