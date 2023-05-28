#include <iostream>

// 如果用快排的话是O(nlogn)的时间复杂度
//   快速选择排序的时间复杂度是O(n)的
//   基于前面的快排模板，我们需要知道第k个数在那半边就可以了，不用去完整的排序。
//   所以左半边有的sl = j-l+1个数，只要这个值大于k就在这般部分递归
//   否则我们需要去另一半区间查找，此时因为少了一个区间，即在另一半区间中找到第k
//  - sl大的数

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1e5 + 10;

int n, k;
int a[N];

void sort(int a[], int l, int r) {
  if (l >= r)
    return;
  int i = l - 1, j = r + 1, tar = a[l + (r - l) / 2];
  while (i < j) {
    do
      i++;
    while (a[i] < tar);
    do
      j--;
    while (a[j] > tar);
    if (i < j)
      swap(a[i], a[j]);
  }
  if (k - 1 >= l && k - 1 <= j)
    sort(a, l, j);
  else
    sort(a, j + 1, r);
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> k;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  sort(a, 0, n - 1);
  cout << a[k - 1] << endl;
}
