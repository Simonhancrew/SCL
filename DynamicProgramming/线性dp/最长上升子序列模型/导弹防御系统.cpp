#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 60;

int a[N],up[N],down[N];
int n,ans;

// 比较类似于之前的导弹系统，因为序列只能增长或者减小，所以没有具体的比较好的办法
// 这里使用dfs搜索出答案
// dfs，遍历导弹，枚举出这个弹道是属于那个子序列的，之后继续dfs,注意回溯的操作
// 如果属于上升子序列，则枚举属于哪个上升子序列（包括新开一个上升子序列）；如果属于下降子序列，可以类似处理。
// 对于上升子序列而言，我们将当前数接在最大的数后面，一定不会比接在其他数列后面更差。
// 最后还需要考虑如何求最小值。因为DFS和BFS不同，第一次搜索到的节点，不一定是步数最短的节点，所以需要进行额外处理。
/*  
    一般有两种处理方式：
    记录全局最小值，不断更新
    迭代加深
*/
void dfs(int u,int su,int sd){
    // 这里是ans
    if(su + sd >= ans) return;
    if(u == n){
        ans = min(ans,su + sd);
        return;
    }
    // 先把这个数放在上升子序列种
    int k = 0;
    while(k < su && up[k] >= a[u]) k++;
    if(k < su){
        int t = up[k];
        up[k] =  a[u];
        dfs(u + 1,su,sd);
        up[k] = t;
    }else{
        up[k] = a[u];
        dfs(u + 1,su + 1,sd);
    }
    
    k = 0;
    while(k < sd && down[k] <= a[u]) k++;
    if(k < sd){
        int t = down[k];
        down[k] = a[u];
        dfs(u + 1,su,sd);
        down[k] = t;
    }else{
        down[k] = a[u];
        dfs(u + 1,su,sd + 1);
    }
}

int main(){
    while(cin >> n,n){
        for(int i = 0;i < n;i++) cin >> a[i];
        ans = n;
        dfs(0,0,0);
        cout << ans << endl;
    }
    return 0;
}