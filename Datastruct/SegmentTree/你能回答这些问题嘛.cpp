#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/02/14

using namespace std;

typedef long long LL;

/*
    因为要维护一个字段和，用线段树来做，需要额外储存一个区间最大字段和
    但是子区间对于这个问题尚不足够覆盖所有的情况，需要多选一个区间的最大最左(右)前缀
    来覆盖跨区间的情况。
    且这个跨区间的子段和情况存在左儿子区间完全覆盖或者右儿子区间完全覆盖之后加上最大子段和前（后）缀
    所以需要多存lmax（左前缀的最大子段和）,rmax,sum（区间和）
*/

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int N = 5e5 + 10;

int n,m;
struct Node
{
    int l,r;
    /*
        区间的最大最左(右)前缀
        区间的最大子段和
    */
    int lmax,rmax,tmax;
    int sum; // 区间和
}tr[N * 4];

int a[N];

void pushup(Node& u,Node& l,Node& r)
{
    u.lmax = max(l.lmax,l.sum + r.lmax);
    u.rmax = max(r.rmax,r.sum + l.rmax);
    u.sum = l.sum + r.sum;
    u.tmax = max(max(l.tmax,r.tmax),l.rmax + r.lmax);
}

/*
    更新父节点操作
*/
void pushup(int u) 
{
    pushup(tr[u],tr[u << 1],tr[u << 1 | 1]);
}

/*
    建树
*/
void build(int u,int l,int r) 
{
    tr[u] = {l,r};
    if(l == r) tr[u] = {l,r,a[r],a[r],a[r],a[r]};
    else
    {
        int mid = l + r >> 1;   
        build(u << 1,l,mid),build(u << 1 | 1,mid + 1,r);
        pushup(u);
    }
}

/*
    调整
*/ 
void modify(int u,int x,int v) 
{
    if(tr[u].l == x && tr[u].r == x) tr[u] = {x,x,v,v,v,v};
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if(x <= mid) modify(u << 1,x,v);
        else modify(u << 1 | 1,x,v);
        pushup(u);
    }
}

Node query(int u,int l,int r) 
{
    if(tr[u].l >= l && tr[u].r <= r) return tr[u];
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if(r <= mid) return query(u << 1,l,r);
        else if(l > mid) return query(u << 1 | 1,l,r);
        else
        {
            auto left = query(u << 1,l,r);
            auto right = query(u << 1 | 1,l,r);
            Node res;
            pushup(res,left,right);
            return res;
        }
    }
}

int main()
{
    fast_cin();
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> a[i];
    build(1,1,n);
    int k,x,y;
    while(m--) 
    {
        cin >> k >> x >> y;
        if(k == 1) 
        {
            if(x > y) swap(x,y);  
            cout << query(1,x,y).tmax << endl;
        }
        else
        {
            modify(1,x,y);
        }
    }
    return 0;
}