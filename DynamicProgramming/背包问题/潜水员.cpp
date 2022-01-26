#include <iostream>
#include <cstring>
#include <algorithm>

// dp[i][j]，氧气拿了i，氮气拿了j体积的时候的最小瓶重，与之前的不超过背包容量不同
// 考虑实际意义，这里要拿的氧气和氮气可以超标！！！多了就从0开始转移，少了就从之前的状态开始转移
// 这里至少达到某一个上限，求最小值

using namespace std;
const int N = 100;

int m,n;
int k;
int dp[N][N];

int main(){
    cin >> m >> n;
    cin >> k;
    memset(dp,0x3f,sizeof dp);
    dp[0][0] = 0;
    for(int i = 0;i < k;i++){
        int a,b,c;
        cin >> a >> b >> c;
        for(int j = m;j >= 0;j--){
            for(int q = n;q >= 0;q--){
                dp[j][q] = min(dp[j][q],dp[max(0,j - a)][max(0,q - b)] + c);
            }
        }
    }
    cout << dp[m][n] << endl;
}