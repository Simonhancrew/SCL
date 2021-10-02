#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e4 + 10;

int q[N],g[N],f[N];
int n,m;

// 旨在用单调队列优化多重背包问题
/*
    比较经典的男人八题，首先回忆一下怎么解多重背包问题
    dp[i][j]的意义就是前i类物品，容积为j的情况下的最大装载利润
    则不难知道dp[i][j] = max(dp[i - 1][j - v] + w，dp[i - 1][j - 2v] + 2w,...,dp[i - 1[j - s * v] + s * w])
    这里不难想到一维的dp方案，只要堆每个i，反向枚举dp[m]->dp[0],遍历所有的i，自然能够得到dp[m]的正确解
    之后继续优化，不难想到，dp[m] = max(dp[m], dp[m-v] + w, dp[m-2*v] + 2*w, dp[m-3*v] + 3*w, ...)
    接下来，dp[0]->dp[m]可以写成如下的形式
    dp[0], dp[v],   dp[2*v],   dp[3*v],   ... , dp[k*v]
    dp[1], dp[v+1], dp[2*v+1], dp[3*v+1], ... , dp[k*v+1]
    dp[2], dp[v+2], dp[2*v+2], dp[3*v+2], ... , dp[k*v+2]
    ...
    dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j]
    显而易见，m 一定等于 k*v + j，其中  0 <= j < v
    所以，我们可以把 dp 数组分成 j 个类，每一类中的值，都是在同类之间转换得到的
    也就是说，dp[k*v+j] 只依赖于 { dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j] }
    所以，我们可以把 dp 数组分成 j 个类，每一类中的值，都是在同类之间转换得到的
    也就是说，dp[k*v+j] 只依赖于 { dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j] }
    所以，我们可以得到
    dp[j]    =     dp[j]
    dp[j+v]  = max(dp[j] +  w,  dp[j+v])
    dp[j+2v] = max(dp[j] + 2w,  dp[j+v] +  w, dp[j+2v])
    dp[j+3v] = max(dp[j] + 3w,  dp[j+v] + 2w, dp[j+2v] + w, dp[j+3v])
    ...
    但是，这个队列中前面的数，每次都会增加一个 w ，所以我们需要做一些转换
    dp[j]    =     dp[j]
    dp[j+v]  = max(dp[j], dp[j+v] - w) + w
    dp[j+2v] = max(dp[j], dp[j+v] - w, dp[j+2v] - 2w) + 2w
    dp[j+3v] = max(dp[j], dp[j+v] - w, dp[j+2v] - 2w, dp[j+3v] - 3w) + 3w
    ...
    这样，每次入队的值是 dp[j+k*v] - k*w
    最后dp[k]需要求的值就是dp[i - 1][q[hh]] + (k - q[hh]) / v * w
*/

int main(){
    cin >> n >> m;
    for(int i = 0;i < n;i++){
        int v,w,s;
        cin >> v >> w >> s;
        memcpy(g,f,sizeof f);
        for(int j = 0;j < v;j++){
            int hh = 0,tt= -1;
            for(int k = j;k <= m;k += v){
                if(hh <= tt && q[hh] < k - s * v) hh++;
                while(hh <= tt && g[q[tt]] - (q[tt] - j) / v * w <= g[k] - (k - j) / v * w ) --tt;
                q[++tt] = k;
                f[k] = g[q[hh]] + (k - q[hh]) / v * w;
            }
        }
    }
    cout << f[m] << endl;
}