#include <iostream>

using namespace std;

const int N = 1e4 + 10;

// from lc 1238, 格雷码=> a ^ (a >> 1)
// 初始是start的话只要给没个数都多异或一个start就可以了

int res[N];
int n, start;

int main() {
  freopen("input.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> start;
  int limit = (1 << n);
  cout << limit << endl;
  for (int i = 0;i < limit;i++) {
    res[i] = i ^ (i >> 1) ^ start;
  }
  for (int i = 0;i < limit;i++) {
    cout << res[i] << ' ';
  }
  cout << endl;
  return 0;
}

