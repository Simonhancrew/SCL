#include <algorithm>
#include <iostream>

//考虑最后一步，拿与不拿最后一个，前面的状态最优。怎么样最后一个才能拿呢？背包还有空间就可以拿，随意需要一个状态
//这个状态标识背包的承重

using namespace std;
const int N = 1e3 + 10;

#if 0
int w[N],v[N];
int dp[N][N];

int main(){
    int m,n;
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> v[i] >> w[i];
    //初始dp[0][x]为0全局不用再初始
    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= m;j++){
            dp[i][j] = dp[i - 1][j];
            if(j >= v[i]){
                dp[i][j] = max(dp[i][j],dp[i - 1][j - v[i]] + w[i]);
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}


//之后我们考虑滚动数组优化，因为只有用到了i-1和i
int main(){
    int m,n;
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> v[i] >> w[i];
    //初始dp[0][x]为0全局不用再初始
    int old = 0,now = 0;
    for(int i = 1;i <= n;i++){
        old = now;
        now = 1 - now;
        for(int j = 0;j <= m;j++){
            dp[now][j] = dp[old][j];
            if(j >= v[i]){
                dp[now][j] = max(dp[now][j],dp[old][j - v[i]] + w[i]);
            }
        }
    }
    cout << dp[now][m] << endl;
    return 0;
}

int f[N];
//最后一维度终极优化
int main(){
    int m,n;
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> v[i] >> w[i];
    //初始dp[0][x]为0全局不用再初始
    for(int i = 1;i <= n;i++){
        //注意逆序，当前的状态会是本层推出来的
        for(int j = m;j >= v[i];j--){;
            f[j] = max(f[j],f[j - v[i]] + w[i]);
            
        }
    }
    cout << f[m] << endl;
    return 0;
}
#endif

// 最后其实发现物品的重量和价值其实可以放到循环的内部读取
int n, m, dp[N];

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int v, w;
    cin >> v >> w;
    for (int j = m; j >= v; j--) {
      dp[j] = max(dp[j], dp[j - v] + w);
    }
  }
  cout << dp[m] << endl;
}