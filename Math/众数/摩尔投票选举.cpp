#include <iostream>

const int N = 1e5 + 10;
// 用于选举出出现次数超过数组长度一半的数
int a[N];

using namespace std;

int main() {
  int n;
  cin >> n;
  int k = 0, candy = 0;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    a[i] = x;
    if (k == 0) {
      candy = x;
      k = 1;
    } else {
      if (candy == x) {
        k++;
      } else {
        k--;
      }
    }
  }
  int k = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] == candy) k++;
  }
  if (k > n / 2)
    cout << candy << endl;
  else
    puts("NO");
  return 0;
}