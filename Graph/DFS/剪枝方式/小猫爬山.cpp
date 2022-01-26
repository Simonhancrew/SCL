#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20;

int n,m;
int sum[N];
int w[N];
int ans = N;

/*
    按照优先搜索分支少的情况，应该先让种的猫占据缆车（这样不合法的时候就可以提前结束了）
    然后考虑一个可行剪枝
*/ 

void dfs(int cat,int car) {
    if(car >= ans) return; // 最优剪枝
    if(cat == n) {
        ans = car;
        return;
    }
    for(int i = 0;i < car;i++) {
        if(sum[i] + w[cat] <= m) { // 可行剪枝
            sum[i] += w[cat];
            dfs(cat + 1,car);
            sum[i] -= w[cat];
        }
    }
    sum[car] = w[cat];
    dfs(cat + 1,car + 1);
    sum[car] = 0;
}

int main(){
    cin >> n >> m;
    for(int i = 0;i < n;i++) cin >> w[i];
    sort(w,w + n,[](int lhs,int rhs) {
        return lhs > rhs;
    });
    dfs(0,0);
    cout << ans << endl;
}