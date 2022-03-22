#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
// Created by Simonhancrew on 2022/03/22

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int INF = 0x3f3f3f3f,N = 2510,M = 6200 * 2 + 10;

int n,m,S,T;
int e[M],ne[M],h[N],w[M],idx;
int dist[N],st[N];

void add(int a,int b,int c)
{
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}

void spfa()
{
    dist[S] = 0;
    queue<int> q;
    q.push(S);
    st[S] = 1;
    while(q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = 0;
        for(int i = h[t];i != -1;i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[t] + w[i]) 
            {
                dist[j] = dist[t] + w[i];
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}

int main(){
    fast_cin();
    memset(h,-1,sizeof h);
    memset(dist,0x3f,sizeof dist);
    cin >> n >> m >> S >> T;
    for(int i = 0;i < m;i++) 
    {
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c),add(b,a,c);
    }
    spfa();
    cout << dist[T] << endl;
    return 0;
}