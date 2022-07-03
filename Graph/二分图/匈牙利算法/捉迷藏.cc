#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/07/02

using namespace std;

/*
  最小重复路径点覆盖
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 210, M = 3e4 + 10;

int n, m;
int match[N];
bool st[N], d[N][N];

bool find(int x)
{
  for (int i = 1; i <= n; i++)
  {
    if (d[x][i] && !st[i])
    {
      auto t = match[i];
      st[i] = true;
      if (t == 0 || find(t))
      {
        match[i] = x;
        return true;
      }
    }
  }
  return false;
}

int main()
{
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n >> m;
  while (m--)
  {
    int a, b;
    cin >> a >> b;
    d[a][b] = 1;
  }
  // 传递闭包
  for (int k = 1; k <= n; k++)
  {
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        d[i][j] |= d[i][k] & d[k][j];
      }
    }
  }
  int res = 0;
  for (int i = 1; i <= n; i++)
  {
    memset(st, 0, sizeof st);
    if (find(i))
      res++;
  }

  cout << n - res << endl;

  return 0;
}