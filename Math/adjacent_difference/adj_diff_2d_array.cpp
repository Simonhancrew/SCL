#include <iostream>
#include <vector>

// Created by Simonhancrew on 2023/12/14

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(NULL);                    \
  cout.tie(NULL)

const int INF = 0x3f3f3f3f;

template<typename T>
void add(T &arr, int a, int b, int c, int d, int x) {
  arr[a][b] += x;
  arr[a][d + 1] -= x;
  arr[c + 1][b] -= x;
  arr[c + 1][d + 1] += x;
}

int main() {
  fast_cin();
  int n{}, m{}, q{};  // NOLINT
  cin >> n >> m >> q;
  vector<vector<int>> arr(n + 2, vector<int>(m + 2));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int x{};
      cin >> x;
      add(arr, i, j, i, j, x);
    }
  }

  while (q--) {                   // NOLINT
    int a{}, b{}, c{}, d{}, x{};  // NOLINT
    cin >> a >> b >> c >> d >> x;
    add(arr, a, b, c, d, x);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      arr[i][j] += arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << arr[i][j] << ' ';
    }
    cout << '\n';
  }

  return 0;
}
