#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/03/24

/*
    实质是一个多源汇的最短路问题，floyd的复杂度是pow(n,3)的
    会超时。考虑对每个结点做起点求最短路。
    1. bellmanford->O(nm),全图每个节点都做一次起点O(n * n * m),依然超时
    2. spafa->O(m)，最坏可能O(nm),同理，有超时的可能，但是可一试
    3. dij朴素，O(n * n + m)，放弃
    4. 堆优化dij，O(mlogn),可以
*/

using namespace std;

typedef long long LL;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int INF = 0x3f3f3f3f,N = 810,M = 2910;

int id[N],d[N],q[N];
int h[N],e[M],ne[M],w[M],idx;
bool st[N];
int n,p,m;

void add(int a,int b,int c) {
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++; 
}

int spfa(int s) {
    memset(d,0x3f,sizeof d);
    int hh = 0,tt = 1;
    d[s] = 0,st[s] = 1,q[0] = s;
    /*
        因为有一个判重的缘故，队列中的数是不会重复的，最多就是节点数N
        因为松弛操作的不确定性，相同元素可能多次进入队列
        最坏下是要开n * m空间的队列的，实质上可以用循环队列替代
    */
    while(hh != tt) {
        int t = q[hh++];
        st[t] = false;
        if(hh == N) hh = 0;
        for(int i = h[t];i != -1;i = ne[i]) {
            int j = e[i];
            if(d[j] > d[t] + w[i]) {
                d[j] = d[t] + w[i];
                if(st[j]) continue;
                st[j] = true;
                q[tt++] = j;
                if(tt == N) tt = 0;
            }
        }
    }
    int res = 0;
    for(int i = 0;i < n;i++) {
        int j = id[i];
        if(d[j] == INF) return INF;
        res += d[j];    
    }
    return res;
}


int main(){
    fast_cin();
    memset(h,-1,sizeof h);
    cin >> n >> p >> m;
    for(int i = 0;i < n;i++) cin >> id[i];
    for(int i = 0;i < m;i++) {
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c),add(b,a,c);
    }
    int res = INF;
    for(int i = 1;i <= p;i++) res = min(res,spfa(i));
    cout << res << endl;
    return 0;
}