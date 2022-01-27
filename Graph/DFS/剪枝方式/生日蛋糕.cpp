#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 25,INF = 1e9;

int n,m;
int minv[N],mins[N];
int H[N],R[N];
int ans = INF;

/*
    从顶往下算，1-m层，枚举的时候从m层自底向上做
    1.优先枚举大R和H
    2.R的范围，[u,min(R[u + 1] - 1,int(sqrt(n - v)))]
    其中，因为每层的值都是递增的，所以肯定是大于等于当前层数的，且最大值
    要考虑总体积减去已经消耗的体积
    3.H的范围同理
    4. 可行性，必须当前的[m,u - 1,-1]层的体积和S累加上[1,u]的最小值要在范围之内
    5. 推一个体积和面积之间的公式
*/

void dfs(int u,int v,int s) {
    // 可行剪枝，当前最下几层的值加上上方的最小面积和体积无法更新或者凑成解
    if(v + minv[u] > n) return;
    if(s + mins[u] >= ans) return;
    if(s + 2 * (n - v) / R[u + 1] >= ans) return;
    
    if(!u) {
        if(n == v) ans = s;
        return;
    }
    /*
        h,r比之前一层的小,且要满足合法性
        v[cur] = r * r * h
        n - v[pre] >= v[cur]
    */ 

    for(int r = min(R[u + 1] - 1,int(sqrt(n - v)));r >= u;r--) {
        for(int h = min(H[u + 1] - 1,(n - v) / r / r);h >= u;h--) {
            int t = 0;
            if(u == m) t = r * r;
            R[u] = r,H[u] = h;
            dfs(u - 1,v + r * r * h,s + 2 * r * h + t);
        }
    }
}

int main(){
    cin >> n >> m;
    for(int i = 1;i <= m;i++) {
        minv[i] = minv[i - 1] + i * i * i;
        mins[i] = mins[i - 1] + i * i * 2; //2 * pi * r * h
    }
    R[m + 1] = H[m + 1] = INF;
    dfs(m,0,0);
    if(ans == INF) ans = 0;
    cout << ans << endl;
    return 0;
}