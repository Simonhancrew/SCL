#include <iostream>

using namespace std;

const int N = 5e5 + 10;
typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

int n;
int a[N], tmp[N];

/*
    一次排序只能改变相邻的元素
    等价于每次只改变一个逆序对，这样求总体逆序对数量就行了
    归并排序过程中求取逆序对数量就行了
*/

LL merge_sort(int l, int r) {
  if (l == r) return 0;

  int mid = l + r >> 1;
  LL res = merge_sort(l, mid) + merge_sort(mid + 1, r);
  int i = l, j = mid + 1, k = 0;
  while (i <= mid && j <= r) {
    if (a[i] <= a[j])
      tmp[k++] = a[i++];
    else {
      res += mid - i + 1;
      tmp[k++] = a[j++];
    }
  }
  while (i <= mid) tmp[k++] = a[i++];
  while (j <= r) tmp[k++] = a[j++];
  for (int i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];
  return res;
}

int main() {
  fast_cin();
  while (cin >> n, n) {
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << merge_sort(0, n - 1) << endl;
  }
  return 0;
}