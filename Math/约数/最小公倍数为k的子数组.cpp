#include <iostream>
#include <vector>

using namespace std;

// 1. 暴力做法，枚举起点和终点，算内部的最小公倍数。公倍数只会变大
// 所以需要注意的点就是及时break

const int N = 1000;

int n,k;

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  cin >> n >> k;
  vector<int> arr(n);
  for(int i = 0;i < n;i++) {
    cin >> arr[i];
  }
  int ans = 0;
  for(int i = 0;i < n;i++) {
    int cur = arr[i], idx = arr[i];
    if(cur > k) continue;
    if(cur == k) ans++;
    for(int j = i + 1;j < n;j++) {
      idx = gcd(cur, arr[j]);
      cur = (arr[j] * cur) / idx;
      if(cur > k) break;
      if(cur == k) ans++;
    }
  }
  cout << ans << endl;
}
