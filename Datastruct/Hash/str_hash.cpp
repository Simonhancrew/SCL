#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>

// Created by Simonhancrew on 2023/11/05

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, P = 13331;
using ULL = uint64_t;

int n, m;
vector<ULL> p;
vector<ULL> s_hash;

void build(const string &s) {
  auto len = s.size();
  for (auto i = 1; i <= n; i++) {
    p[i]      = p[i - 1] * P;
    s_hash[i] = s_hash[i - 1] * P + s[i - 1];
  }
}

ULL get(int l, int r) {
  return s_hash[r] - s_hash[l - 1] * p[r - l + 1];
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m;
  // reserver is slower than resize
  // maybe push_back is still check size, hh
  p.resize(n + 1);
  s_hash.resize(n + 1);
  p[0] = 1;
  s_hash[0] = 1;
  string s;
  cin >> s;
  build(s);
  while (m--) {
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    if (get(l1, r1) == get(l2, r2)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }
  return 0;
}
