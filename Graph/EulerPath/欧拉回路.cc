#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/07/12

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                                                             \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr);                                                            \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10, M = 4e5 + 10;

int type;
int n, m;
int h[N],e[M],ne[M],w[M],idx;
int din[N],dout[N];
bool used[M];
int ans[M],cnt;

void add(int a,int b) {
  e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

void dfs(int u) {
  for(int &i = h[u];i != -1;) {
    if(used[i]) {
      i = ne[i];
      continue;
    }
    used[i] = true;
    if(type == 1) used[i ^ 1] = true;

    int t;
    if(type == 1) {
      t = i / 2 + 1;
      if(i & 1) t = -t;
    }else{
      t = i + 1;
    }

    int j = e[i];
    i = ne[i];
    dfs(j);

    ans[++cnt] = t;
  }
}


int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> type;
  cin >> n >> m;
  memset(h,-1,sizeof h);
  for(int i = 0;i < m;i++) {
    int u,v;
    cin >> u >> v;
    din[v]++,dout[u]++;
    add(u,v);
    if(type == 1){
      add(v,u);
    }
  }
  if(type == 1) {
    for(int i = 1;i <= n;i++) {
      if((din[i] + dout[i]) & 1) {
        cout << "NO" << '\n';
        return 0;
      }
    }
  }else{
    for(int i = 1;i <= n;i++) {
      if(din[i] != dout[i]) {
        cout << "NO" << '\n';
        return 0;
      }
    }
  }
  for(int i = 1;i <= n;i++) {
    if(h[i] != -1) {
      dfs(i);
      break;
    }
  }
  if(cnt < m) {
    cout << "NO" << '\n';
    return 0;
  }
  cout << "YES" << '\n';
  for(int i = cnt;i;i--) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
  return 0;
} 