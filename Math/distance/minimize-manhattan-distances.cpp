#include <algorithm>
#include <iostream>
#include <set>
#include <vector>


// Created by Simonhancrew on 2024/07/09

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

// 曼哈顿转切比雪夫距离的技巧，绕原点旋转90度之后扩大根号2倍
// 删除一个点，让其余的点的最大距离最小

int n{};

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  int x{}, y{};
  vector<vector<int>> points;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    points.push_back({x, y});
  }
  multiset<int> sx, sy;
  for (const auto &p : points) {
    sx.insert(p[0] + p[1]);
    sy.insert(p[0] - p[1]);
  }
  int ans = INT_MAX;
  for (const auto &p : points) {
    int x = p[0] + p[1];
    int y = p[0] - p[1];
    sx.erase(sx.find(x));
    sy.erase(sy.find(y));
    auto dx = *sx.rbegin() - *sx.begin();
    auto dy = *sy.rbegin() - *sy.begin();
    ans     = min(ans, max(dx, dy));
    sx.insert(x);
    sy.insert(y);
  }
  cout << ans << '\n';
  return 0;
}
