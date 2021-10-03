#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e4 + 10;

int dp[N];

// 装箱问题改01背包，要体积最大，把每件物品的价值量等价为体积就行了

int main()
{
    int n,m;
    cin >> m;
    cin >> n;
    for(int i = 0;i < n;i++){
        int w;
        cin >> w;
        for(int j = m;j >= w;j--) dp[j] = max(dp[j],dp[j - w] + w);
    }
    cout << m - dp[m] << endl;
}