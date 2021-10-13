#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e3 + 10;

// 判断物品是否被选，等价一个最短路，求出路径
// 因为确定了字典序最小，所以一个贪心的思路就是倒推的时候从第一个物品开始判断是否需要
// 但是如果dp还是按照之前的定义，dp[i][j]前i个数，重量j的背包的最大价值无法确定在某个位置的时候
// 到底能不能选i，选了的话可能导致后面状态无法逆推到0
// 为了确定这个时候的i是可选的，需要dp遍历的时候做点别的处理
// 就是从n开始推，既是dp[i][j]的意义编程从i个元素往后的元素中，重量位j的最大价值
// 这样就保证了最后逆推的时候顺序遍历下，这个i一定是可以选的

int dp[N][N];
int n,m;
int v[N],w[N];

int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> v[i] >> w[i];
    for(int i = n;i >=1;i--){
        for(int j = 0;j <= m;j++){
            dp[i][j] = dp[i + 1][j];
            if(j >= v[i]) dp[i][j] = max(dp[i][j],dp[i + 1][j - v[i]] + w[i]);
        }
    }
    int j = m;
    for(int i = 1;i <= n;i++){
        if(j >= v[i] && dp[i][j] == dp[i + 1][j - v[i]] + w[i]){
            cout << i << ' ';
            j -= v[i];
        }
    }
    return 0;
}