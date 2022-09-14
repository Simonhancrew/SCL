#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2022/02/17

using namespace std;

/*
    非常特殊的扫描线 + 线段树的用法，直接硬背就好
    线段树里存的离散区间，seg是线段，总共2 * n条
    一个矩形的一对线段堆成的操作，前+ 1，后-1（cnt）
    只对cnt > 0的线段统计值就是最后的面积
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1e5 + 10;

// 扫描线的线段
struct Segment {
  double x, y1, y2;
  int k;
  bool operator<(const Segment &t) const { return x < t.x; }
} seg[N * 2];

// 利用线段树存线段的区间
struct Node {
  int l, r;
  int cnt;     // 叠加次数
  double len;  // 当前节点线段的长度
} tr[N * 8];

int n;
vector<double> ys;

void build(int u, int l, int r) {
  tr[u] = {l, r, 0, 0};
  if (l != r) {
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
  }
}

void pushup(int u) {
  /*
      这里感觉r其实是一个区间多少的统计
      第多少个区间，也可以看作下一个区间的起点
      实际的到终点需要 + 1
  */
  if (tr[u].cnt)
    tr[u].len = ys[tr[u].r + 1] - ys[tr[u].l];
  else if (tr[u].l != tr[u].r) {
    /*
        底下可能更新了，上传就可以
    */
    tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
  } else
    tr[u].len = 0;  // l == r,jb区间都没有
}

int find(double x) { return lower_bound(ys.begin(), ys.end(), x) - ys.begin(); }

void modify(int u, int l, int r, int k) {
  if (tr[u].l >= l && tr[u].r <= r) {
    tr[u].cnt += k;
    pushup(u);
  } else {
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) modify(u << 1, l, r, k);
    if (r > mid) modify(u << 1 | 1, l, r, k);
    pushup(u);
  }
}

int main() {
  fast_cin();
  int t = 1;
  while (cin >> n, n) {
    double x1, x2, y1, y2;
    ys.clear();
    for (int i = 0, j = 0; i < n; i++) {
      cin >> x1 >> y1 >> x2 >> y2;
      seg[j++] = {x1, y1, y2, 1}, seg[j++] = {x2, y1, y2, -1};
      ys.push_back(y1), ys.push_back(y2);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    /*
        ys存的是点，但是线段树维护的是区间
        假设有2 * n个y坐标点，区间就是2 * （n - 1）
        ys.size() - 2
    */
    build(1, 0, ys.size() - 2);

    sort(seg, seg + n * 2);

    double res = 0;
    for (int i = 0; i < 2 * n; i++) {
      if (i > 0) res += tr[1].len * (seg[i].x - seg[i - 1].x);
      modify(1, find(seg[i].y1), find(seg[i].y2) - 1, seg[i].k);
    }

    printf("Test case #%d\n", t++);
    printf("Total explored area: %.2lf\n\n", res);
  }
  return 0;
}