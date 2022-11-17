#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

// Created by Simonhancrew on 2022/11/17

using namespace std;

// 找子序列的一个做法
// 暴力的方法就是针对words里的每一个word和s做一次双指针匹配
// 优化来自将s中所有的s[i]映射为[a..z, [idx]]的map
// map的value的list一定是升序的，因此针对word的每一个words[i]
// 二分合法的idx并不断更新就可以了

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

vector<string> words;
string s;
int n;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> s;
  cin >> n;
  words.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> words[i];
  }
  // 针对每个字母构建一个增序idx
  vector<vector<int>> mp(26);
  for (int i = 0; i < n; i++) {
    mp[s[i] - 'a'].push_back(i);
  }
  int ans = words.size();
  // 针对words[i], 遍历内部的words[i][j]
  for (const auto &x : words) {
    if (x.size() > s.size()) {
      ans--;
      continue;
    }
    
    int idx = -1;
    for (auto c : x) {
      auto &arr = mp[c - 'a'];
      if (arr.empty() || arr.back() <= idx) {
        ans--;
        break;
      }
      // 二分找到合法解
      int l = 0, r = arr.size() - 1;
      while (l < r) {
        int mid = l + r >> 1;
        if (arr[mid] > idx)
          r = mid;
        else
          l = mid + 1;
      }
      idx = arr[l];
    }
  }
  cout << ans << endl;
  return 0;
}
