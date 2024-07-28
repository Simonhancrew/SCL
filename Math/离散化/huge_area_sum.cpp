#include <algorithm>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2024/07/28

using namespace std;

// 离线做法，实质是要做前缀和，但是2 * 1e9长度的数组是开不出来的，太大了
// 但是询问数量是比较少的，可以将线化作点(一个离散化的点包含了一个区域)，缩小区域，做一个离散化。别的没出现过的点都没有用到，没有任何信息。
// 收集所有要处理的区域，去重排序，映射成一个离散的数组all。处理[l,
// r]的区间和实质就映射到了[all[lower_bound(l)], all[lower_bound(r)]]的区间和

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int n, m;
vector<PII> add, query;
vector<int> all;
vector<LL> s;

int find(int x) {
  int l = -1, r = all.size();
  while (l + 1 < r) {
    int mid = (l + r) >> 1;
    if (all[mid] <= x)
      l = mid;
    else
      r = mid;
  }
  return l;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m;
  all.reserve(n + m * 2);
  for (int i = 0; i < n; i++) {
    int x, c;
    cin >> x >> c;
    add.emplace_back(x, c);
    all.push_back(x);
  }
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    query.emplace_back(l, r);
    all.push_back(l);
    all.push_back(r);
  }
  sort(all.begin(), all.end());
  all.erase(unique(all.begin(), all.end()), all.end());
  s.resize(all.size() + 1);
  for (const auto &[x, c] : add) {
    int pos = find(x);
    s[pos] += c;
  }
  for (int i = 1; i < all.size(); i++)
    s[i] += s[i - 1];
  for (const auto &[l, r] : query) {
    int lpos = find(l);
    int rpos = find(r);

    cout << s[rpos] - (lpos == 0 ? 0 : s[lpos - 1]) << '\n';
  }
  return 0;
}
