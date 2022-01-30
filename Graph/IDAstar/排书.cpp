#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20;

int w[N];
int cp[5][N];
int t,n;


/*
    此时的启发函数，每次调位置，都能改变3个数的位置关系
*/
int f() {
    int cnt = 0;
    for(int i = 0;i + 1 < n;i++) {
        if(w[i] + 1 != w[i + 1]) cnt ++; 
    }
    return (cnt + 2) / 3;
}

// u是当前的深度，depth是最大可以枚举的深度
bool dfs(int u,int depth) {
    if(f() + u > depth) return false;
    if(f() == 0) return true; // 全部有序就无需调整
    
    // 枚举调整的长度和最后调整长度插入的坐标点
    for(int len = 1;len <= n;len++){
        for(int l = 0;l + len - 1 < n;l++) {
            int r = l + len - 1;
            for(int k = r + 1;k < n;k++) {
                memcpy(cp[u],w,sizeof w);
                int i,j;
                for(i = l,j = r + 1;j <= k;i++,j++) w[i] = cp[u][j];  
                for(j = l;j <= r;i++,j++) w[i] = cp[u][j];
                if(dfs(u + 1,depth)) return true;
                memcpy(w,cp[u],sizeof cp[u]);
            }
        }
    }
    return false;
}

int main(){
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0;i < n;i++)  cin >> w[i];
        int depth = 0;
        while(depth < 5 && !dfs(0,depth)) depth++;
        if(depth >= 5) puts("5 or more");
        else cout << depth << endl;
    }
    return 0;
}