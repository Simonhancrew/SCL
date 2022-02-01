#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e5 + 10;

/*
    因为y[1] - y[n]是一个[1,n]的集合，当前求山谷等价于对于每个节点
    求其左右有多少个比其大的数。先从左到右遍历一次，找出左侧的bigger数，
    再从右到左遍历一次找出左侧的bigger数。最后相乘求和即可。山峰的求法同理
*/

#define fast_cin() ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long LL;

int n;
int a[N];
int tr[N];
int bigger[N],lower[N];

int lowbit(int x) {
    return x & -x;
} 

void add(int x,int k){
    for(int i = x;i <= n;i += lowbit(i)) tr[i] += k;
}

int sum(int x) {
    int tot = 0;
    for(int i = x;i;i -= lowbit(i)) tot += tr[i];
    return tot;
}

int main(){
    fast_cin();
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) {
        int cur = a[i];
        bigger[i] = sum(n) - sum(cur);
        lower[i] = sum(cur - 1);
        add(cur,1);
    }
    memset(tr,0,sizeof tr);
    LL res1 = 0,res2 = 0;
    for(int i = n;i >= 1;i--) {
        int cur = a[i];
        res1 += bigger[i] * (LL)(sum(n) - sum(cur));
        res2 += lower[i] * (LL) sum(cur - 1);
        add(cur,1);
    }
    cout << res1 << ' ' << res2 << endl;
    return 0;
}