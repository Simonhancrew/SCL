#include <iostream>

using namespace std;

const int N = 110;



int n;
int w[N];

/*
    u是当前搜索的层数，depth是最大搜索层数
    只要当前搜索的层数到了最大的层数，就看看有没有搜到答案
    搜到了直接返回，否则就把层数+1
*/ 
bool dfs(int u,int depth) {
    if(u == depth) return w[u - 1] == n;
    /*
        一个排除等效冗余的剪枝，1 + 4 == 2 + 3
        开一个数组标记这一轮在当前点搜过哪些数
    */ 
    int st[N] = {0};

    // 枚举a -> w[0,u-1],b -> w[0,u-1],求和C(N,2) + N
    for(int i = u - 1;i >= 0;i--) {
        for(int j = i;j >= 0;j--) {
            int s = w[i] + w[j];
            if(s > n) continue; // 可行剪枝
            if(s <= w[u - 1] || st[s]) continue; // w应满足底层且没出现过

            st[s] = true;
            w[u] = s;
            if(dfs(u + 1,depth)) return true;
        }
    }
    return false;
}

int main(){
    w[0] = 1;
    while(cin >> n,n) {
        int depth = 1;
        while(!dfs(1,depth)) depth++;
        for(int i = 0;i < depth;i++) cout << w[i] << ' ';
        cout << endl;
    }
    return 0;
}