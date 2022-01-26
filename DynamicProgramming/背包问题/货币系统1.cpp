#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using LL = long long;
const int N = 3e3 + 10;

LL dp[N];
int n,m;

// 一个简单的完全背包问题，转化成方案计数
// 几个套路就是dp[0] = 1,之后完全背包的形式的二维遍历
// 最后的+=统计方案总数

int main()
{
    cin >> n >> m;
    dp[0] = 1;
    for(int i = 0;i < n;i++){
        int a;
        cin >> a;
        for(int j = a;j <= m;j++){
            dp[j] += dp[j - a];
        }
    }
    cout << dp[m] << endl;
}