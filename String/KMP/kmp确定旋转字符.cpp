#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

// Created by Simonhancrew on 2022/09/29

using namespace std;

// 旋转字符类的做法比较确定，len(s1) != len(s2)的时候直接false
// 否则s1 + s1中只要能找出s2就是合法的

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

std::string s1, s2;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> s1 >> s2;
  if (s1.size() != s2.size()) {
    cout << "No" << '\n';
    return 0;
  }
  if (s1 == s2) {
    cout << "Yes\n";
    return 0;
  }
  string s = s1 + s1;
  int n = s2.size(), m = s.size();
  vector<int> ne(n);
  ne[0] = -1;
  for (int i = 1, j = -1; i < n; i++) {
    while (j != -1 && s2[j + 1] != s2[i])
      j = ne[j];
    if (s2[j + 1] == s2[i])
      j++;
    ne[i] = j;
  }
  for (int i = 0, j = -1; i < m; i++) {
    while (j != -1 && s2[j + 1] != s[i])
      j = ne[j];
    if (s[i] == s2[j + 1])
      j++;
    if (j == n - 1) {
      // cout << i << ' ' << j << '\n';
      // j = ne[j];
      cout << "Yes\n";
      return 0; 
    }
  }
  cout << "No" << '\n';
  return 0;
}