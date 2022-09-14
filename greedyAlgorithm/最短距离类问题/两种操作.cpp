#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e4 + 10;

int q[N], d[N];
int n, m;

#if 0
// 正向考虑的话，BFS最小步数可以做
int main()
{
    cin >> n >> m;
    memset(d,0x3f,sizeof d);
    d[n] = 0;
    int hh = 0,tt = 0;
    q[0] = n;
    while(hh <= tt) 
    {
        int t = q[hh++];
        int ne[] = {t - 1,t * 2};
        for(auto x : ne) 
        {
            if(x >= 1 && x < N && d[x] > d[t] + 1) 
            {
                d[x] = d[t] + 1;
                q[++tt] = x;
            }
        }
    }
    cout << d[m] << endl;
    return 0;
}
#endif

/*
    贪心解法，反向考虑，因为n只能乘和-，对于m的拟操作就是+和 /= 2
*/
#include <iostream>

using namespace std;

int m, n, res;

int main() {
  cin >> n >> m;
  while (n != m) {
    if (m < n)
      m++;
    else if (m & 1)
      m++;
    else
      m /= 2;
    res++;
  }
  cout << res << endl;
  return 0;
}
