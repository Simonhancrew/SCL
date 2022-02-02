#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/02/02

using namespace std;

typedef long long LL;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int INF = 0x3f3f3f3f,N = 1e5 + 10;

/*
    从后往前做，假设当前的idx位置，前面有h[idx]头牛比他高，其就是目前剩余可以选的
    牛中第h[idx] + 1位的（下标从1开始）
    假设一个权值都是1的数组a，用树状数组维护。前缀和就是身高在[1,n]中的排序值
    每次选择的时候，2分出当前的第h[idx] + 1大高度的牛
*/

int n;
int h[N];
int tr[N];
int ans[N];

int lowbit(int x) {
    return x & -x;
}

void add(int x,int c) {
    for(int i = x;i <= n;i += lowbit(i)) tr[i] += c;
}

int sum(int x) {
    int res = 0;
    for(int i = x;i;i -= lowbit(i)) res += tr[i];
    return res;
}

int main(){
    fast_cin();
    cin >> n;
    for(int i = 2;i <= n;i++) cin >> h[i];
    for(int i = 1;i <= n;i++) tr[i] = lowbit(i); // 因为权值全部1，tr的值就是覆盖数组a的长度
    for(int i = n;i;i--) {
        int l = 1,r = n,k = h[i] + 1;
        while(l < r) {
            int mid = l + r >> 1;
            if(sum(mid) >= k)  r = mid;
            else l = mid + 1;
        }
        ans[i] = r;
        add(r,-1);
    }
    for(int i = 1;i <= n;i++) cout << ans[i] << endl;
    return 0;
}