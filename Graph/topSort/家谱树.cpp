#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/04/02

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int INF = 0x3f3f3f3f,N = 110,M = N * N / 2;

int e[M],ne[M],h[N],idx;
int q[N],in[N];
int n;

void add(int a,int b) {
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

void topsort(){
    int hh = 0,tt = -1;
    for(int i = 1;i <= n;i++) {
        if(!in[i]) q[++tt] = i;
    }
    while(hh <= tt) {
        int t = q[hh++];
        for(int i = h[t];i != -1;i = ne[i]) {
            int j = e[i];
            if(--in[j] == 0) q[++tt] = j;
        }
    }
    
}

int main(){
    fast_cin();
    cin >> n;
    memset(h,-1,sizeof h);
    for(int i = 1;i <= n;i++) {
        int son;
        while(cin >> son,son) {
            add(i,son);
            in[son]++;
        }
    }
    topsort();
    for(int i = 0;i < n;i++) cout << q[i] << ' ';
    return 0;
}