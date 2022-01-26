#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e3 + 10;

int dp[N],m,n;

int main()
{
    cin >> m >> n;
    for(int i = 0;i < n;i++){
        int v,w;
        cin >> v >> w;
        for(int j = m;j >= v;j--) dp[j] = max(dp[j],dp[j - v] + w);
    }
    cout << dp[m] << endl;
}