#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Created by Simonhancrew on 2023/08/01

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

string s, p;
vector<int> ne;
int n, m;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> p >> m >> s;
  ne.resize(n);
  ne[0] = -1;
  for (int i = 1, j = -1; i < n; i++) {
    while (j != -1 && p[i] != p[j + 1])
      j = ne[j];
    if (p[i] == p[j + 1]) ++j;
    ne[i] = j;
  }
  
  for (int i = 0, j = -1;i < m;i++) {
    while (j != -1 && s[i] != p[j + 1]) j = ne[j];
    if (s[i] == p[j + 1]) ++j;
    if (j == n - 1) {
      cout << i - n + 1 << ' ';
      j = ne[j];
    }
  }
  return 0;
}
