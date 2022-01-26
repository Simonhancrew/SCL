#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 110,M = 1 << 10;

// 滚动数组的技巧，具体位置&1就可以了

int n,m;
int f[2][M][M]; // f[i][j][k]前i行中，最后一行的状态是k,倒数第二行是j的最多炮台数
int g[N];
char t;
int cnt[M];
vector<int> st;

bool check(int u){
    for(int i = 0;i < m - 1;i++){
        if((u >> i & 1) && (u >> i + 1 & 1) | (u >> i + 2 & 1)) return false;
    } 
    return true;
}

int count(int u){
    int res = 0;
    while(u){
        res += u & 1;
        u >>= 1;
    }
    return res;
}

int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        for(int j = 0;j < m;j++){
            cin >> t;
            if(t == 'H') g[i] += 1 << j;
        }
    }

    for(int i = 0;i < 1 << m;i++){
        if(check(i)){
            st.push_back(i);
            cnt[i] = count(i);
        }
    }

    for(int i = 1;i <= n + 2;i++){
        for(int j = 0;j < st.size();j++){
            for(int k = 0;k < st.size();k++){
                for(int u = 0;u < st.size();u++){
                    int a = st[j],b = st[k],c = st[u];
                    if(a & c | a & b | b & c) continue; // 所有的炮台不能相互攻击到
                    if(g[i] & b || g[i - 1] & a) continue; // 不能有位置冲突
                    f[i & 1][j][k] = max(f[i & 1][j][k],f[i - 1 & 1][u][j] + cnt[b]);
                }
            }
        }
    }
    cout << f[n + 2 & 1][0][0] << endl;
    return 0;
}

