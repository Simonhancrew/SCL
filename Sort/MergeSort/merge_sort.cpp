#include <iostream>

using namespace std;

// Created by Simonhancrew on 2023/05/30

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

//归并排序分为三步
// 1 选中间点
// 2 归：递归的排序左半边的右半边
// 3 并：利用一个额外的数组，合并两个已经排序的部分

const int INF = 0x3f3f3f3f, N = 1e5 + 10;

int n;
int a[N], tmp[N];

//自底向上
void sort(int a[], int l, int r) {
  if (l >= r) {
    return;
  }
  int mid = l + (r - l) / 2;
  sort(a, l, mid), sort(a, mid + 1, r);
  int i = l, j = mid + 1, k = 0;
  while (i <= mid && j <= r) {
    if (a[i] <= a[j]) {
      tmp[k++] = a[i++];
    } else {
      tmp[k++] = a[j++];
    }
  }
  while (i <= mid)
    tmp[k++] = a[i++];
  while (j <= r)
    tmp[k++] = a[j++];
  for (int i = l, j = 0; i <= r; i++, j++) {
    a[i] = tmp[j];
  }
}

int main() {
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  sort(a, 0, n - 1);
  for (int i = 0; i < n; i++)
    cout << a[i] << ' ';
  cout << '\n';
  return 0;
}
