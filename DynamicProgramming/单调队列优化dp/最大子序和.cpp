#include <iostream>

using namespace std;

/*
    不难想到最开始转换成一个前缀和区间求解的问题，遍历两次的复杂度n**2
    考虑以i结尾的最优解就是：s[i] - s[i - j],其中j是区间的长度，[1,m]
    不难推理到让s[i - j]最小就可以达到效果
    一个区间中的最小值，不难联想到单调队列
*/

const int N = 3e5 + 10,INF = 0x3f3f3f3f;

#define fast_cin() ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)

int s[N],q[N];
int n,m;

int main(){
    fast_cin();
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> s[i];
    for(int i = 1;i <= n;i++) s[i] += s[i - 1];
    int hh = 0,tt = 0;
    int res = -INF;
    for(int i = 1;i <= n;i++){
        if(q[hh] < i - m) hh++;
        res = max(res,s[i] - s[q[hh]]);
        // 单调队列，比你晚来的还比你更有优势，你就可以out了。你永远不会被考虑
        while (hh <= tt && s[q[tt]] >= s[i]) tt--; 
        q[++tt] = i;
    }
    cout << res << endl;
    return 0;
}