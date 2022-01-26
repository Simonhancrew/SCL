#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
typedef long long LL;

/*
    思路比较多，f[i]是考虑前i个牛的最大价值，其中第i头牛不选时f[i] = f[i - 1]
    第i头牛被选时，最多能被选一个区间k之前的牛
    f[i] = f[i - j - 1] + s[i] - s[i - j],其中j在[1,k]中取值
    f[i] = max(g(i - j))  + s[i],只要维护一个关于g的递减区间就可以了
    其中i - j在[i - k,i - 1]中
    另外特判g(0)，连续区间的长度就是i，前面的部分就是0，不需要转移，直接返回0

    当然也可以考虑成连续k + 1个数中，至少有一个不被选。最后用全部的和减去min(f[n - k]~f[n])就可以了
    则f[i]就是在连续k + 1个数中，第i个数被选，且价值最小的情况
    和烽火传递的转移方式很类似
*/

int n,k;
LL e[N],q[N],f[N];

LL g(int i) {
    if(!i) return 0;
    return f[i - 1] - e[i];
}

int main(){
    cin >> n >> k;
    for(int i = 1;i <= n;i++) {
        cin >> e[i];
        e[i] += e[i - 1]; 
    }
    int hh = 0,tt = 0;
    for(int i = 1;i <= n;i++){
        if(q[hh] < i - k) hh++;
        f[i] = max(f[i - 1],g(q[hh]) + e[i]);
        while(hh <= tt && g(q[tt]) <= g(i)) tt--;
        q[++tt] = i;
    }
    cout << f[n] <<endl;
    return 0;
}