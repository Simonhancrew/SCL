#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// Created by Simonhancrew on 2023/08/07

using namespace std;

// 逐字符匹配可能的candidate, 按照字典序选择3个, 不考虑错误

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 2e4 + 10;

int n, idx;
int tr[N][26];
string pattern;
vector<string> candi;
unordered_map<int, int> lhs, rhs;

void add(const std::string& s, int id) {
  int u = 0;
  for (const auto x : s) {
    auto c = x - 'a';
    if (!tr[u][c]) {
      tr[u][c] = ++idx;
      lhs[tr[u][c]] = id;
    }
    rhs[tr[u][c]] = id;
    u = tr[u][c];
  }
}

PII query(const std::string &s) {
  int u = 0;
  PII res{};
  for (const auto x : s) {
    auto c = x - 'a';
    if (!tr[u][c])
      return {-1, -1};
    res.first  = lhs[tr[u][c]];
    res.second = rhs[tr[u][c]];
    u          = tr[u][c];
  }
  return res;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  candi.reserve(n);
  for (int i = 0;i < n;i++) {
    string s;
    cin >> s;
    candi.push_back(std::move(s));
  }
  cin >> pattern;
  sort(candi.begin(), candi.end());
  for (int i = 0;i < n;i++) add(candi[i], i);
  for (int i = 0;i < pattern.size();i++) {
    auto [l, r] = query(pattern.substr(0, i + 1));
    if (l == -1) {
      cout << "NO ANS\n";
    } else {
      for (int j = l; j <= min(l + 2, r); j++) {
        cout << candi[j] << ' ';
      }
      cout << '\n';
    }
  }
  return 0;
}
