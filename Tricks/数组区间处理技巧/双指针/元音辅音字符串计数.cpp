#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Created by Simonhancrew on 2025/03/12

using namespace std;

// 至少包含5个元音字母至少一个，且包含辅音字母恰好k个

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

string s;
int k;
unordered_set<char> st = {'a', 'e', 'i', 'o', 'u'};

// 等价转化位求解至少包含5个元音字母至少一个，且包含辅音字母至少k个
LL f(const std::string &s, int k) {
  int n   = s.size();
  LL ans  = 0;
  int cnt = 0;
  int l   = 0;
  unordered_map<char, int> mp;
  for (const auto c : s) {
    if (st.count(c)) {
      mp[c]++;
    } else {
      cnt++;
    }
    while (cnt >= k && mp.size() == st.size()) {
      if (st.count(s[l])) {
        mp[s[l]]--;
        if (mp[s[l]] == 0) {
          mp.erase(s[l]);
        }
      } else {
        cnt -= 1;
      }
      ++l;
    }
    ans += l;
  }
  return ans;
}

void solve(const std::string &s, int k) {
  // 等价转化位至少包含5个元音字母至少一个，且包含辅音字母至少k个 -
  // 至少包含5个元音字母至少一个，且包含辅音字母至少k+1个
  LL res = f(s, k) - f(s, k + 1);
  cout << res << '\n';
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> s >> k;
  solve(s, k);
  return 0;
}
