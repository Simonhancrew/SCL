#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20;

// 每个公司可以分配0-3台机器，每个分配方案的收益都不一样
// 直接就等价一个分组背包了,从这几家公司中选，背包容量为m
// 选分配方案0-3
// 因为每个背包的选法之和容积有关，所以可以不用改变dp的顺序
// 可以和求方案的01背包对比 

int dp[N][N];
int w[N][N];
int n,m;
int rt[N];

int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> w[i][j];
        }
    }
    
    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= m;j++){
            for(int k = 0;k <= j;k++){
                dp[i][j] = max(dp[i][j],dp[i - 1][j - k] + w[i][k]);
            }
        }
    }
    
    cout << dp[n][m] << endl;
    int j = m;
    for(int i = n;i >= 1;i--){
        for(int k = 0;k <= m;k++){
            if(dp[i][j] == dp[i - 1][j - k] + w[i][k]) {
                j -= k;
                rt[i] = k;
                break;
            }
        }
    }
    
    for(int i = 1;i <= n;i++){
        cout << i << ' ' << rt[i] << endl;
    }
    return 0;
}