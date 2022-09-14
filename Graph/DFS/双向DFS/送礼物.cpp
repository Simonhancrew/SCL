#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 47;

typedef long long LL;  // 相加可能爆int

int w, n, k;
int g[N];
int weight[1 << 25], cnt = 1;
int ans = 0;

// 前半部分的搜索，记录在weight，u是当前搜索深度，s是当前和
void dfs1(int u, int s) {
  if (u == k) {
    weight[cnt++] = s;
    return;
  }
  dfs1(u + 1, s);
  if ((LL)g[u] + s <= w) dfs1(u + 1, g[u] + s);  // 可行性剪枝
}

// 后半部分的搜索，wei有序唯一
void dfs2(int u, int s) {
  if (u == n) {
    int l = 0, r = cnt - 1;
    while (l < r) {
      int mid = l + r + 1 >> 1;
      if ((LL)weight[mid] + s <= w)
        l = mid;
      else
        r = mid - 1;
    }
    ans = max(ans, s + weight[l]);
    return;
  }
  dfs2(u + 1, s);
  if ((LL)g[u] + s <= w) dfs2(u + 1, g[u] + s);
}

int main() {
  cin >> w >> n;
  for (int i = 0; i < n; i++) cin >> g[i];
  // 剪枝1,先搜大的
  sort(g, g + n, [](int lhs, int rhs) { return lhs >= rhs; });
  // 前半部分空间
  k = n / 2 + 2;
  dfs1(0, 0);
  // 排序之后去重
  sort(weight, weight + cnt);
  cnt = unique(weight, weight + cnt) - weight;
  // 二分一个最大的ans = weight[x] + s,weight是有序的
  dfs2(k, 0);
  cout << ans << endl;
  return 0;
}