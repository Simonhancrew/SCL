#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 40;

int n;
int a[N];
int f[N][N],g[N][N]; // 记录路径的方法就是多开一个数组记录转移的路径

void dfs(int l,int r){
    if(l > r) return;
    int t = g[l][r];
    cout << t << ' ';
    dfs(l,t - 1);
    dfs(t + 1,r);
}

int main(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    
    for(int len = 1;len <= n;len++){
        for(int l = 1;l + len - 1 <= n;l++){
            int r = l + len - 1;
            if(len == 1) f[l][r] = a[l],g[l][r] = l;
            else{
                for(int k = l;k <= r;k++){
                    int left = l == k ? 1 : f[l][k - 1];
                    int right = r == k ? 1 : f[k + 1][r];
                    int score = left * right + a[k];
                    if(score > f[l][r]){
                        f[l][r] = score;
                        g[l][r] = k;
                    }
                }
            }
        }
    }
    cout << f[1][n] << endl;
    dfs(1,n);
    return 0;
}