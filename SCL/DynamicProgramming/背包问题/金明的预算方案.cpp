#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 32010,M = 70;
typedef pair<int,int> PII;

PII master[M];
vector<PII> slave[M];
int dp[N];

// 抽象到最后就是一个简答的分组背包，每个组里选的话必须选主件
// 首先如果选这个组的话，主件一定要被选，之后二进制枚举其他的附件有没有被选就可以了
// 最后如果当前的体积够用的话就可以做一个状态的转移

int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= m;i++){
        int v,p,q;
        cin >> v >> p >> q;
        p *= v;
        if(!q) master[i] = {v,p};
        else slave[q].push_back({v,p});
    }
    
    for(int i = 1;i <= m;i++){
        for(int j = n;j >= 0;j--){
            for(int k = 0;k < 1 << slave[i].size();k++){
                int v = master[i].first,w = master[i].second;
                for(int off = 0;off < slave[i].size();off++){
                    if(k >> off & 1){
                        v += slave[i][off].first;
                        w += slave[i][off].second;
                    }
                }
                if(j >= v) dp[j] = max(dp[j],dp[j - v] + w);
            }
        }
    }
    cout << dp[n] << endl;
    return 0;
}