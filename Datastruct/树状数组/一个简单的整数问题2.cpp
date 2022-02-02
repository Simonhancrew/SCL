#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/02/02

using namespace std;

typedef long long LL;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int INF = 0x3f3f3f3f,N = 1e5 + 10;

/*
    加的操作比较好做，减去的操作可以推一个公式
    假设区间是[1,x]

    a1 = b1
    a2 = b1 + b2
    a3 = b1 + b2 + b3
    ...
    ax = b1 + ... + ax
    给右边全部补全成  => b1 + .. + bx
    同时多加一项sum(b1,bx),总公式可以简化为
    sum(a1,ax) =（a1 + ...+ ax） * (x + 1) - (1 * b1 + 2 * b2 + ...x * bx) 
    多储存一个b[i] * i的树状数组就可了
*/

LL tr1[N],tr2[N];
int a[N];
int n,m;

int lowbit(int x) {
    return x & -x;
}

void add(LL tr[],int x,LL k) {
    for(int i = x;i <= n;i += lowbit(i)) tr[i] += k;
}

LL sum(LL tr[],int x) {
    LL tot = 0;
    for(int i = x;i;i -= lowbit(i)) {
        tot += tr[i];
    }
    return tot;
}

LL presum(int x) {
    return sum(tr1,x) * (x + 1) - sum(tr2,x);
}

int main(){
    fast_cin();
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) {
        int b = a[i] - a[i - 1];
        add(tr1,i,b);
        add(tr2,i,(LL)b * i);
    }
    while(m--) {
        char op;
        cin >> op;
        if(op == 'C') {
            int l,r,d;
            cin >> l >> r >> d;
            add(tr1,l,d),add(tr1,r + 1,-d);
            add(tr2,l,l * d),add(tr2,r + 1,(r + 1) * (-d));
        }else{
            int l,r;
            cin >> l >> r;
            cout << presum(r) - presum(l - 1) << endl;
        }
    }
    return 0;
}