#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e3 + 10;

int f[N];
int n, m, v, w;

int main() {
  cin >> n >> m;
  memset(f, -0x3f, sizeof f);
  for (int i = 0; i < n; i++) {
    for (int j = m; j >= v; j--) {
      f[j] = max(f[j], f[j - v] + w);
    }
  }
  if (f[m] < 0)
    cout << -1 << endl;
  else
    cout << f[m] << endl;
  return 0;
}