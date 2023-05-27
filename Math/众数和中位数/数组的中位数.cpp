#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2023/05/27

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e4;

int n;
int a[N];

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  sort(a, a + n);
  // 集中处理偶数和奇数
  // n是偶数时, (2 * m + 1) / 2和(2 * m + 2) / 2是不一样的
  // n是奇数时, (2 * m + 1 + 1) / 2和(2 * m + 1 + 2) / 2是一样的
  int lhs = (n + 1) / 2, rhs = (n + 2) / 2;
  int cnt = 0;
  cout << (a[lhs] + a[rhs]) / 2.0 << '\n';
  return 0;
}
