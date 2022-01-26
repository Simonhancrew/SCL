#include <iostream>
#include <algorithm>
#include <cstring>

/*
    当前数能转换，当且仅当其约数的和小于当前数。每个数的约数之和是固定的
    等价于找到树的最大直径
    建树的过程借鉴筛法，可以转换的连一条边
    随后树形dp找最大直径
    int dfs(u){
        st[u] = true

        dist = d1 = d2 = 0
        for(sons of u){
            d = dfs(son)
            if d >= d1 {
                d1,d2 = d,d1
            }else if d > d2{
                d2 = d
            }
        }
        return dist + w
    }
*/

using namespace std;

const int N = 5e4 + 10;

int n,ans;
int sum[N];
int h[N],e[N],ne[N],idx;
int st[N];

void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

int dfs(int u){
    st[u] = 1;
    
    int dist = 0;
    int d1 = 0,d2 = 0;
    for(int i = h[u];i != -1;i = ne[i]){
        int j = e[i];
        if(!st[j]){
            int d = dfs(j);
            dist = max(dist,d);
            if(d >= d1) d2 = d1,d1 = d;
            else if(d > d2) d2 = d;
        }
    }
    ans = max(ans,d1 + d2);
    return dist + 1;
}

int main(){
    cin >> n;
    // 线性筛的思路
    for(int i = 1;i <= n;i++){
        for(int j = 2;j <= n / i;j++){
            sum[i * j] += i;            
        }
    }
    memset(h,-1,sizeof h);
    for(int i = 2;i <= n;i++){
        if(sum[i] < i) {
            add(sum[i],i);
        }
    }
    for(int i = 1;i <= n;i++){
        if(!st[i]) dfs(i);
    }
    cout << ans << endl;
    return 0;
}