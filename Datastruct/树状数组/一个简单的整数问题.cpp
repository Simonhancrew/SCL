#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/02/02

using namespace std;

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10;

/*
    树状数组里面存一个差分数组就可以了
*/

LL tr[N];
int a[N];
int n, m;

int lowbit(int x) { return x & -x; }

void add(int x, int k) {
  for (int i = x; i <= n; i += lowbit(i)) tr[i] += k;
}

LL sum(int x) {
  LL tot = 0;
  for (int i = x; i; i -= lowbit(i)) {
    tot += tr[i];
  }
  return tot;
}

int main() {
  fast_cin();
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) add(i, a[i] - a[i - 1]);
  while (m--) {
    char op;
    cin >> op;
    if (op == 'C') {
      int l, r, d;
      cin >> l >> r >> d;
      add(l, d), add(r + 1, -d);
    } else {
      int x;
      cin >> x;
      cout << sum(x) << endl;
    }
  }
  return 0;
}