#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// dp[i][j] 体积恰好为j的情况下的最大价值
// 再开一个数组记录方案，g[i][j]表示从前i个数中选，恰好体积为j的时候的最佳方案的方案数

const int N = 1e3 + 10,MOD = 1e9 + 7;
int f[N],g[N];
int n,m;

int main(){
    cin >> n >> m;
    g[0] = 1;
    for(int i = 0;i < n;i++){
        int v,w;
        cin >> v >> w;
        for(int j = m;j >= v;j--){
            int mx = max(f[j],f[j - v] + w);
            int t = 0;
            if(mx == f[j]) t += g[j];
            if(mx == f[j - v] + w) t = (g[j - v] + t) % MOD;
            f[j] = mx,g[j] = t;
        }
    }
    // int res = f[m];
    int res = -1;
    for(int i = 0;i <= m;i++) res=max(res,f[i]);
    int sum = 0;
    for(int i = 0;i <= m;i++) {
        if(res == f[i]) sum = (sum + g[i]) % MOD;
    }
    cout << sum << endl;
}