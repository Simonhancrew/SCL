#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*
  正常来讲，欧拉图存的边如果不按照点的大小排序的话，输出是没有序的
  其次，因为先搜的点在回溯的时候才会加进ans数组中，所以需要逆序输出
  奇数开始，一个点能搜多次，需要覆盖所有的边。
*/

const int N = 510,M = 1100;

int m;
int g[N][N];
int d[N];
int ans[M],cnt;

void dfs(int u) {
  for(int i = 1;i <= 500;i++) {
    if(g[u][i]) {
      g[u][i]--,g[i][u]--;
      dfs(i);
    }
  }
  ans[++cnt] = u;
}

int main(){
  cin >> m;
  for(int i = 0;i < m;i++) {
    int u,v;
    cin >> u >> v;
    g[u][v]++,g[v][u]++;
    d[u]++,d[v]++;
  }
  
  int start = 1;
  while(!d[start]) start++;
  for(int i = start;i <= 500;i++) {
    if(d[i] & 1) {
      start = i;
      break;
    }
  }
  
  dfs(start);
  for(int i = cnt;i;i--) {
    cout << ans[i] << '\n';
  }
  return 0;
}
