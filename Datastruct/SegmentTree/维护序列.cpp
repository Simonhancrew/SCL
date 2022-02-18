#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/02/18

using namespace std;

typedef long long LL;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int N = 1e5 + 10;

int n,p,m;
int a[N];

/*
    因为需要做乘和加的区间操作，需要考虑一个计算顺序
    先add再乘：(sum + add) * mul,pushdown的时候不好处理add的变化
    先mul再乘，pushdown的时候add也倍增就行了
*/

struct Node
{
    int l,r;
    int sum,add,mul;
}tr[N * 4];

/*
    不下沉的时候永远不考虑pushdown，只考虑当前节点的pushup
*/
void pushup(int u)
{   
    tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % p; 
}

/*
    修改当前节点的add和mul值
*/
void change(Node& t,int add,int mul)
{
    t.sum = ((LL)t.sum * mul + (LL)(t.r - t.l + 1) * add) % p;
    t.mul = (LL)t.mul * mul % p;
    t.add = ((LL)t.add * mul + add) % p;
}

void pushdown(int u)
{
    change(tr[u << 1],tr[u].add,tr[u].mul);
    change(tr[u << 1 | 1],tr[u].add,tr[u].mul);
    tr[u].add = 0,tr[u].mul = 1;
}

void build(int u,int l,int r)
{
    if(l == r) tr[u] = {l,r,a[r],0,1};
    else
    {
        tr[u] = {l,r,0,0,1}; 
        int mid = l + r >> 1;
        build(u << 1,l,mid),build(u << 1 | 1,mid + 1,r);
        pushup(u);
    }
}


void modify(int u,int l,int r,int add,int mul)
{
    if(tr[u].l >= l && tr[u].r <= r) change(tr[u],add,mul); // 完全包含，修改，回溯
    else
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(l <= mid) modify(u << 1,l,r,add,mul);
        if(r > mid) modify(u << 1 | 1,l,r,add,mul);
        pushup(u);
    }
}

int query(int u,int l,int r)
{
    if(tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL sum = 0;       
    if(l <= mid) sum += query(u << 1,l,r);
    if(r > mid) sum = (sum + query(u << 1 | 1,l,r)) % p;
    return sum; 
}

int main()
{
    fast_cin();
    cin >> n >> p;    
    for(int i = 1;i <= n;i++) cin >> a[i];
    build(1,1,n);
    cin >> m;
    int op,l,r,d;
    while(m--)
    {
        cin >> op >> l >> r;
        if(op == 1) 
        {
            cin >> d;
            modify(1,l,r,0,d);
        }
        else if(op == 2)
        {
            cin >> d;
            modify(1,l,r,d,1);
        }
        else cout << query(1,l,r) << endl;
    }
    return 0;
}