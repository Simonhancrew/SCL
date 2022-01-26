#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// 1. 在时间规定之内走完，不能回头
// 2. 这里求的是最小值，所以第一行第一列不能从之前的0走过来（全局变量初始为0）
// 3. 区别于摘花生，dp[i][j]是走到i,j的最小值，转移方程有区别

const int N = 110,INF = 1e9;
int a[N][N];
int dp[N][N];
int n;

int main()
{
    cin >> n;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cin >> a[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(i == 1 && j == 1) dp[i][j] = a[i][j];
            else{
                dp[i][j] = INF;
                if(i > 1) dp[i][j] = min(dp[i - 1][j] + a[i][j],dp[i][j]);
                if(j > 1) dp[i][j] = min(dp[i][j - 1] + a[i][j],dp[i][j]);
            }
        }
    }
    cout << dp[n][n] << endl;
    return 0;
}

#if 0
// 数字三角，最小值模型，python3辅助理解
n = int(input())
INF = int(1e9)
a = []
dp = [[INF] * n for _ in range(n)]

for _ in range(n):
    b = list(map(int,input().split()))
    a.append(b)

for i in range(n):
    for j in range(n):
        if i == 0 and j == 0:
            dp[i][j] = a[i][j]
        else:
            if i > 0: dp[i][j] = min(dp[i - 1][j] + a[i][j],dp[i][j])
            if j > 0: dp[i][j] = min(dp[i][j - 1] + a[i][j],dp[i][j])

print(dp[n - 1][n - 1])
#endif