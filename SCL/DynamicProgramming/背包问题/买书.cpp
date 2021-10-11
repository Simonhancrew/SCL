#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e3 + 10;


// 还是三重循环考虑2维的

#if 0
int dp[5][N];

int main(){
    int n;
    cin >> n;
    dp[0][0] = 1;
    int a[] = {0,10,20,50,100};
    for(int i = 1;i <= 4;i++){
        for(int j = 0;j <= n;j++){
            for(int k = 0;k * a[i] <= j;k++){
                dp[i][j] += dp[i - 1][j - k * a[i]];
            } 
        }
    }
    cout << dp[4][n] << endl;
}
#endif

// 推公式优化，和数字组合类似的问题解法

int dp[N];

int main(){
    int n;
    cin >> n;
    dp[0] = 1;
    int a[] = {10,20,50,100};
    for(int i = 0;i < 4;i++){
        for(int j = a[i];j <= n;j++){
            dp[j] += dp[j - a[i]]; 
        }
    }
    cout << dp[n] << endl;
}