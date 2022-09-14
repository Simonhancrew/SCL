#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 5e3 + 10;

typedef pair<int, int> PII;

// 代码抽象出来不难，思路比较难
/*
    桥梁不能相交，所以先把任意河岸一边的排序，为了保持对应关系，存pair就行了
    对岸的要不冲突，就刚好是一个上升序列
    可以转化成一个LIS模型
*/

PII a[N];
int dp[N];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) scanf("%d%d", &a[i].first, &a[i].second);
  sort(a, a + n);

  int res = 0;
  for (int i = 1; i <= n; i++) {
    dp[i] = 1;
    for (int j = 1; j < i; j++) {
      if (a[i - 1].second > a[j - 1].second) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
    res = max(res, dp[i]);
  }
  cout << res << endl;
}