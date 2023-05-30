#include <iostream>


// Created by Simonhancrew on 2023/05/30

using namespace std;
using LL = long long;

const int N = 1e5 + 10;

#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

int n;
LL ans;
int a[N], tmp[N];

void sort(int a[], int l, int r) {
  if (l >= r) {
    return;
  }
  int mid = l + r >> 1;
  sort(a, l, mid), sort(a, mid + 1, r);
  int i = l, j = mid + 1, k = 0;
  while (i <= mid && j <= r) {
    if (a[i] <= a[j]) {
      tmp[k++] = a[i++];
    } else {
      ans += mid - i + 1;
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
  cout << ans << endl;
}
