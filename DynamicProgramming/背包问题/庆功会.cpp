#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// 首先考虑最简单的二维多重背包
#if 0
const int N = 510,M = 6e3 + 10;
int dp[N][M];
int v[N],w[N],s[N];
int n,m;

int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> v[i] >> w[i] >> s[i];
    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= m;j++){
            for(int k = 0;k <= s[i] && k * v[i] <= j;k++){
                dp[i][j] = max(dp[i][j],dp[i - 1][j - k * v[i]] + w[i] * k);
            }
        }
    }
    cout << dp[n][m] << endl;
}
#endif

// 考虑到所有的背包问题的第一维都可以用倒序遍历优化掉
#if 0
const int N = 510,M = 6e3 + 10;
int v[N],w[N],s[N];
int dp[M];
int n,m;


int main(){
    cin >> n >> m;
    for(int i = 0;i < n;i++){
        cin >> v[i] >> w[i] >> s[i];
    }
    for(int i = 0;i < n;i++){
        for(int j = m;j >= 0;j--){
            for(int k = 0;k <= s[i] && k * v[i] <= j;k++){
                dp[j] = max(dp[j],dp[j - k * v[i]] + k * w[i]);
            }
        }
    }
    cout << dp[m] << endl;
}
#endif
// 总结一下背包问题，给定了一个限制的空间，和一堆序列给出的物品，能够选取的数量要参考具体环境,选定一个最大价值的问题都可以往背包上面靠
// 然后注意一下背包的变种问题，比如数字组合和装箱问题，
const int N = 6e3 + 10;
int dp[N];
int n,m,v,w,s;

int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        cin >> v >> w >> s;
        for(int j = m;j >= 0;j--){
            for(int k = 0;k <= s && k * v <= j;k++){
                dp[j] = max(dp[j],dp[j - k * v] + k * w);
            }
        }
    }
    cout << dp[m] << endl;
}