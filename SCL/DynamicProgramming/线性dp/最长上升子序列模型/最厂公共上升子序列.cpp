#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N =  3e3 + 10;

int a[N],b[N];
int dp[N][N]; // dp[i][j] a的前i和b的前j序列中，且以b[j]结尾的最长公共子序列的长度
int n;

#if ORIGIN
int main()
{
    cin >> n;  
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) cin >> b[i];
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            // 不包含a[i]
            dp[i][j] = dp[i - 1][j];
            // 包含a[i]
            if(a[i] == b[j]){
                dp[i][j] = max(dp[i][j],1);
                // 枚举包含a[i]的时候，b序列中倒数第二个数是哪一个
                for(int k = 1;k < j;k++){
                    if(b[j] > b[k]) dp[i][j] = max(dp[i - 1][k] + 1,dp[i][j]);
                }
            }
        }
        
    }
    int res = 0;
    for(int i = 1;i <= n;i++) res = max(res,dp[n][i]);
    cout << res << endl;   
}
#endif


int main(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) cin >> b[i];

    for(int i = 1;i <= n;i++){
        int maxv = 1;
        // 优化的思路在第三种循环的时候，一直在求一个max(dp[i - 1][k] + 1,dp[i][j])
        // 因为实际上a[i] == b[j]的，所以，第三维循环里面的判断是可以从if(b[j] > b[k]]) -> if(a[i] > b[k])，实际上判断条件与j已经无关了
        // 但是我们只要记录这个dp[i - 1][k]的最大值就可以了
        // 特殊的，a[i] > b[j]的时候，这个k的范围往后推了，可以更新
        for(int j = 1;j <= n;j++){
            dp[i][j] = dp[i - 1][j];
            if(a[i] == b[j]) dp[i][j] = max(dp[i][j],maxv);
            if(b[j] < a[i]) maxv = max(maxv,dp[i - 1][j] + 1);
        }
    }

    int res = 0;
    for(int i = 1;i <= n;i++) res = max(res,dp[n][i]);
    cout << res << endl;
    return 0;
}