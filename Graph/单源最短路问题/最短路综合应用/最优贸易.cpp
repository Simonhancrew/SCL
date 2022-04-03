#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

// Created by Simonhancrew on 2022/04/03

using namespace std;

/*
    一个dp问题，找划分点，先求出[1,i]中购买物品最小的花费w
    然后找出[i,n]中卖出物品最大的收益u.要保证连通，可以构造一个反向图，后半部分的用
    最后的获利就是u - w
    存在环和多次入队且出队时不一定是最小的花费，所以dij是不能选用的
*/

typedef long long LL;
typedef pair<int,int> PII;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int INF = 0x3f3f3f3f,N = 1e5 + 10,M = 2e6 + 10;

int n,m;
int w[N];
int h[N],rh[N],e[M],ne[M],idx;
int dmin[N],dmax[N];
bool st[N];

void add(int h[],int a,int b) {
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

void spfa(int dist[],int s,int h[],bool flag) {
    queue<int> q;
    memset(st,0,sizeof st);
    
    if(flag) memset(dist,0x3f,N * 4);
    
    dist[s] = w[s];
    q.push(s);
    st[s] = true;
    
    while(q.size()) {
        auto t = q.front();
        q.pop();
        st[t] = false;
        for(int i = h[t];~i;i = ne[i]) {
            int j = e[i];
            if(flag && dist[j] > min(dist[t],w[j]) || !flag && dist[j] < max(dist[t],w[j])) {
                if(flag) dist[j] = min(dist[t],w[j]);
                else dist[j] = max(dist[t],w[j]);
                
                if(!st[j]) {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }
    
}

int main(){
    fast_cin();
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> w[i];
    memset(h,-1,sizeof h);
    memset(rh,-1,sizeof rh);
    for(int i = 0;i < m;i++) {
        int a,b,c;
        cin >> a >> b >> c;
        add(h,a,b),add(rh,b,a);
        if(c == 2) add(h,b,a),add(rh,a,b);
    }
    spfa(dmax,n,rh,false);
    spfa(dmin,1,h,true);
    int res = 0;
    for(int i = 1;i <= n;i++) res = max(res,dmax[i] - dmin[i]); 
    cout << res << endl;
    return 0;
}