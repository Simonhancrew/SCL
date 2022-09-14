#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/02/12

using namespace std;

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1e5 + 10;

int n, m, t;
int row[N], col[N], s[N], c[N];

/*
    可以转化成一个均分纸牌问题
    针对行：
        要让每行的尽可能的平均，他要拿出给相邻的行（行内每列换暖用没有）
        这里就看做一个和均分问题，其总和一定要是行数的倍数(不能整除就无解)
        推一个每行给相邻行的公式
    列同理
*/

LL work(int n, int a[]) {
  for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
  if (s[n] % n) return -1;
  int avg = s[n] / n;
  c[1] = 0;
  for (int i = 2; i <= n; i++) c[i] = s[i - 1] - (i - 1) * avg;
  sort(c + 1, c + n + 1);
  LL res = 0;
  for (int i = 1; i <= n; i++) res += abs(c[i] - c[(n + 1) / 2]);
  return res;
}

int main() {
  fast_cin();
  cin >> n >> m >> t;
  while (t--) {
    int x, y;
    cin >> x >> y;
    row[x]++, col[y]++;
  }
  LL r = work(n, row);
  LL c = work(m, col);
  if (r != -1 && c != -1)
    cout << "both " << r + c << endl;
  else if (r != -1)
    cout << "row " << r << endl;
  else if (c != -1)
    cout << "column " << c << endl;
  else
    cout << "impossible" << endl;
  return 0;
}