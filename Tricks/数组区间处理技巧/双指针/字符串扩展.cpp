#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2022/11/25

using namespace std;

// from lc 809
// 针对基本串p，和扩展结果串s，求一个他们相对相同位置相同字符的长度len
// 能扩展的话结果串的len一定不会比基本串小，且当长度小于3的时候这二者是要相等的

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

string s;
vector<string> words;
int n;

void solve() {
  vector<PII> rec;
  int m = s.size();
  for (int i = 0; i < m; i++) {
    int j = i + 1;
    while (j < m && s[j] == s[i])
      j++;
    rec.emplace_back(s[i] - 'a', j - i);
    i = j - 1;
  }
  int ans    = 0;
  auto check = [&rec](string &w) {
    if (w.size() > s.size())
      return false;
    int m = w.size(), k = 0;
    for (int i = 0; i < m; i++) {
      if (k == rec.size())
        return false;
      if (w[i] - 'a' != rec[k].first)
        return false;
      int j = i + 1;
      while (j < m && w[j] == w[i])
        j++;
      int difw = j - i, difs = rec[k].second;
      if (difw > difs)
        return false;
      if (difw != difs && difs < 3)
        return false;
      k++, i = j - 1;
    }
    return k == rec.size();
  };
  for (auto &w : words) {
    if (check(w))
      ans++;
  }
  cout << ans << endl;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> s >> n;
  words.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> words[i];
  }
  solve();
  return 0;
}