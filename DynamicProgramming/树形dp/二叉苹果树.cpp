#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*
    有依赖背包问题的简化，f[i][j],以i为根节点的子树，包含i的连通块的边数不超过j的方案
    其中要求最大值
    状态转移的时候预留父节点的连边
    f[i][j] = max(f[i][j - k - 1] + f[son[i]][k] + edge[i])
*/

#define fast_cin() ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

const int N = 110,M = 2 * N;

int q,n;
int e[M],ne[M],w[M],h[N],idx;
int f[N][N];

void add(int a,int b,int c){
    e[idx] = b,w[idx] = c,ne[idx] = h[a],h[a] = idx++;
}

void dfs(int u,int father){
    for(int i = h[u];i != -1;i = ne[i]){
        if(e[i] == father) continue;
        dfs(e[i],u);
        for(int j = q;j >= 0;j--){
            for(int k = 0;k + 1 <= j;k++){
                f[u][j] = max(f[u][j],f[u][j - k - 1] + f[e[i]][k] + w[i]);
            }
        }
    }
}

int main(){
    fast_cin();
    cin >> n >> q;
    memset(h,-1,sizeof h);
    for(int i = 1;i < n;i++){
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c),add(b,a,c);
    }
    dfs(1,-1);
    cout << f[1][q] << endl;
    return 0;
}