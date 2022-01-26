#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*
    最大值最小，自然想到二分
    确定空题长度能不能在t时间内完成
    f[i]，从[1,i]中，完成题目i时，空题长度不超过limit的最小时间花费
    需要注意的是边界问题，最长空题段是limit的时候，[i - limit,i - 1]中都可以是空的，所以左边界在i - limit - 1
    最后在[n - limit,n]中，只要花费不超过t，都可以认为是可以完成的
*/

const int N = 5e4 + 10;

int n,t;
int q[N],f[N],a[N];

bool check(int limit){
    int hh = 0,tt = 0;
    for(int i = 1;i <= n;i++){
        if(hh <= tt && q[hh] < i - limit - 1) hh++;
        f[i] = f[q[hh]] + a[i];
        while(hh <= tt && f[q[tt]] >= f[i]) tt--;
        q[++tt] = i;
    }
    for(int i = n - limit;i <= n;i++){
        if(f[i] <= t) {
            return true;
        }
    }
    return false;
}

int main(){
    cin >> n >> t;
    for(int i = 1;i <= n;i++) cin >> a[i];
    int l = 0,r = n;
    while(l < r){
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << endl;
    return 0;
}