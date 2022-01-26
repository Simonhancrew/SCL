#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1510;
int e[N],ne[N],h[N],idx;
bool st[N];
int f[N][2];
int n;

/*
    树形dp，f[u][0]代表当前节点不放置守卫的时候的，能够观潮到下方所有的边的最小守卫个数
    f[u][0] = sum(f[sons[u]][1])
    f[u][1] = sum(min(f[sons[u]][1],f[sons[u]][0]))    
*/

void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}


// 向下搜索，无向边不用考虑回搜
void dfs(int u){
    f[u][0] = 0,f[u][1] = 1;
    for(int i = h[u];i != -1;i = ne[i]){
        int j = e[i];
        dfs(j);
        f[u][0] += f[j][1];
        f[u][1] += min(f[j][0],f[j][1]);
    }
}

int main(){
    while(scanf("%d",&n) == 1){
        // reset init env
        idx = 0;
        memset(h,-1,sizeof h);
        memset(st,0,sizeof st);
        for(int i = 0;i < n;i++){
            int id,cnt;
            scanf("%d:(%d)",&id,&cnt);
            while(cnt--){
                int ver;
                scanf("%d",&ver);
                add(id,ver);
                st[ver] = true;
            }
        }
        //find root
        int root = 0;
        while(st[root]) root++;
        dfs(root);
        // get min ans
        printf("%d\n",min(f[root][0],f[root][1]));      
    }
    return 0;
}