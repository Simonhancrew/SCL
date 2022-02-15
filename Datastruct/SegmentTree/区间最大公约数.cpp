#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/02/15

using namespace std;

typedef long long LL;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int N = 5e5 + 10;

int n,m;
LL a[N];

/*
    同样动态区间调整和询问，线段树，看存一个公因数够不够
    gcd(a,b)和gcd(a,a - b)有相同的公因数
    所以用线段树维护一个原数组的差分数组，多存一个前缀和值
    这样gcd[l,r] = gcd(a[l],gcd(a(l + 1,r)))
    既可以递推成左边a[l]和右边的最大公因数的gcd
*/

struct Node
{
    int l,r;
    LL sum,d; // 差分数组的和，区间最大公因数
}tr[N * 4];


LL gcd(LL a,LL b)
{
    return b ? gcd(b,a % b) : a;
}


void pushup(Node& u,Node& l,Node& r) 
{
    u.sum = l.sum + r.sum;
    u.d = gcd(l.d,r.d);
}

void pushup(int u) {
    pushup(tr[u],tr[u << 1],tr[u << 1 | 1]);
}

void build(int u,int l,int r) 
{
    tr[u] = {l,r};
    if(l == r) {
        LL cur = a[r] - a[r - 1];
        tr[u] = {l,r,cur,cur};
    }else{
        int mid = l + r >> 1;
        build(u << 1,l,mid),build(u << 1 | 1,mid + 1,r);
        pushup(u);
    }
}

Node query(int u,int l,int r)
{
    if(tr[u].l >= l && tr[u].r <= r) return tr[u];
    else{
        int mid = tr[u].l + tr[u].r >> 1;
        if(r <= mid) return query(u << 1,l,r);
        else if(l > mid) return query(u << 1 | 1,l,r);
        else{
            auto left = query(u << 1,l,r);
            auto right = query(u << 1 | 1,l,r);
            Node res({0,0,0,0});
            pushup(res,left,right);
            return res;
        }
    }
}

void modify(int u,int x,LL v) 
{
    if(tr[u].l == x && tr[u].r == x) 
    {
        LL cur = tr[u].sum + v;
        tr[u] = {x,x,cur,cur};
    }
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if(x <= mid) modify(u << 1,x,v);
        else modify(u << 1 | 1,x,v);
        pushup(u);
    }
}

int main()
{
    fast_cin();
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> a[i];
    build(1,1,n);
    int l,r;
    LL d;
    string op;
    while(m--) {
        cin >> op >> l >> r;
        if(op == "C")
        {
            cin >> d;
            modify(1,l,d);
            if(r + 1 <= n) modify(1,r + 1,-d); // 当n不够r + 1的时候右边无界
        }
        else
        {
            auto left = query(1,1,l);
            Node right({0,0,0,0});
            if(l + 1 <= r)  right = query(1,l + 1,r);
            cout << abs(gcd(left.sum,right.d)) << endl;
        }
    }
    return 0;
}