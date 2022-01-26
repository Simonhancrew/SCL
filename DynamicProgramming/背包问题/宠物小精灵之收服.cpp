#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010,M = 510;

// 一个二维背包费用问题
// 花费1：精灵球
// 花费2：皮卡丘的体力
// 价值：收服精灵的数量,收服一个+1

int n,m,k;
int v1[N],v2[N];
int dp[N][M];

int main(){
    cin >> n >> m >> k;
    // for(int i = 1;i <= k;i++){
    //     cin >> v1[i] >> v2[i];
    // }
    int v1,v2;
    for(int i = 1;i <= k;i++){
        cin >> v1 >> v2;
        for(int j = n;j >= v1;j--){
            for(int h = m;h > v2;h--){
                dp[j][h] = max(dp[j][h],dp[j - v1][h - v2] + 1); 
            }
        }
    }
    // 求最大收服数的时候的最小体力剩余
    // 只要找到这个最大收服数的最小体力支出就可以了
    int r = m;
    while(r > 0 && dp[n][m] == dp[n][r]) r--;
    cout << dp[n][m] << ' '  << m - r << endl;
    return 0;
}