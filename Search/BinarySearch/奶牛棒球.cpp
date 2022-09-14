#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e3 + 10;

/*
    二分不仅仅针对一个排序的区间，还可以针对具有二段性的一个连续序列(不针对本题而言)
    比如前半个序列满足某种性质，后半个序列不满足这种性质，一样可以二分
    数据范围1k,暴力枚举前两个，然后在[j + 1,n]的范围里二分第三个数
    最后一个数的范围在[2 * y - x,3 * y - 2 * x]之间
    n ** 2  * log(n)
*/

int w[N];
int n;

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> w[i];
  sort(w, w + n);
  int ans = 0;
  for (int i = 0; i < n - 2; i++) {
    for (int j = i + 1; j < n - 1; j++) {
      auto up = upper_bound(w + j, w + n, 3 * w[j] - 2 * w[i]);
      auto down = lower_bound(w + j, w + n, 2 * w[j] - w[i]);
      ans += up - down;
    }
  }
  cout << ans << endl;
  return 0;
}