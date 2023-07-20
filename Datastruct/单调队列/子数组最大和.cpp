#include <iostream>
#include <queue>

// Created by Simonhancrew on 2023/07/20

using namespace std;

// 求子数组的最大和，快速的求取一段区间的和->前缀和
// 从左到右，找到最小的合法减数->这一段的和最大

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

const int N = 1e5 + 10;

int n;
int a[N], s[N];

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + a[i - 1];
  }
  deque<int> q;
  q.push_back(0);
  int res = INT_MIN;
  for (int i = 1; i <= n; i++) {
    auto cur = s[i] - s[q.front()];
    while (!q.empty() && s[i] <= s[q.back()]) {
      q.pop_back();
    }
    q.push_back(i);
    res = max(res, cur);
  }
  cout << res << '\n';
  return 0;
}
