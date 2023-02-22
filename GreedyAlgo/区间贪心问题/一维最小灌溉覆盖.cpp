#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using PII = pair<int, int>;

const int N = 1e4 + 10;
int arr[N];
int n;

// arr是点i能够灌溉的半径，求最小点覆盖
// 首先处理一下覆盖的半径，然后按照左端点排序
// 贪心的选择当前能够选择的most right
// 然后更新区间的当前的区间右端点
// 下一次覆盖的最小左端点就是当前更新过的右端点

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 0;i <= n;i++) {
    cin >> arr[i];
  }
  vector<PII> rec(n + 1);
  for (int i = 0;i <= n;i++) {
    rec.emplace_back(i - arr[i], i + arr[i]);
  }
  int res = 0, r = 0;
  sort(rec.begin(), rec.end());
  for (int i = 0;i <= n;i++) {
    int j = i, mr = -1;
    while (j <= n && rec[j].first <= r) {
      mr = max(mr, rec[j].second);
    }
    if (mr == -1) {
      cout << -1 << '\n';
        return 0;
    }
    res++;
    if (res >= n) {
      cout << res << '\n';
      return 0;
    }
    r = mr;
    i = j - 1;
  }
  cout << -1 << '\n';
  return 0;
}


