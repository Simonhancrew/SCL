#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>

using namespace std;

const int N = 2e4 + 10;

int n, x, y, z;
map<int, int> mp;

/*
    离散化 + 差分
    现象最暴力的方法，遍历所有的温度，看每个温度下的值是多少，最后去一个max
    但是温度的范围很大，在[0,1e9]之内，暴力做是一个n * T的时间复杂度
    但是观察到每头牛的产奶温度区间是[a[i],b[i]]的，所以可以考虑差分加离散化的方式
*/

int main() {
  cin >> n >> x >> y >> z;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    mp[0] += x;
    mp[a] = mp[a] - x + y;
    mp[b + 1] = mp[b + 1] - y + z;
  }
  int res = 0, cur = 0, key = 0;
  for (auto [k, v] : mp) {
    cur += v;
    if (cur > res) {
      res = cur;
      key = k;
    }
  }
  cout << res << endl;
}