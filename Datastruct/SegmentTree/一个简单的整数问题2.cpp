#include <iostream>

using namespace std;

typedef long long LL;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int N = 1e5 + 10;

/*
    区间调整，线段树。因为设计区间调整，所以多了一个
    pushdown的操作，在需要沉到子节点的时候需要做一次（modify + query）
    主要就是将add中的修改惰性传递到子区间中，然后将修改的标记清零。

*/

int a[N];
int m,n;

struct Node
{
    int l,r;
    int add;
    LL sum;
}tr[N * 4];

void pushup(int u) 
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u)
{
    Node &root = tr[u],&lhs = tr[u << 1],&rhs = tr[u << 1 | 1];
    if(root.add)
    {
        lhs.add += root.add,lhs.sum += (LL)(lhs.r - lhs.l + 1) * root.add;
        rhs.add += root.add,rhs.sum += (LL)(rhs.r - rhs.l + 1) * root.add;
        root.add = 0;
    }
}

void build(int u,int l,int r)
{
    if(l == r) tr[u] = {l,r,0,a[r]};
    else
    {
        tr[u] = {l,r};
        int mid = l + r >> 1;
        build(u << 1,l,mid),build(u << 1 | 1,mid + 1,r);
        pushup(u);
        // cout << l << ' ' << r << ' ' << tr[u].sum << endl;
    }
}

/*
    调整时，只有当前节点u的区间完全被[l,r]覆盖才做修改
    否则就下沉，修改子树，先pushdown，然后pushup，传递修改
*/
void modify(int u,int l,int r,int d)
{
    if(tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].sum += (LL)(tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
    }
    else
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(l <= mid) modify(u << 1,l,r,d);
        if(r > mid) modify(u << 1 | 1,l,r,d);
        pushup(u);
    }
}

/*
    query一直，只有节点u的区间完全被[l,r]覆盖的时候才做一个
    传递。否则就下沉，同理需要pushdown，将可能存在的惰性修改
    赋予下层。最后做一个递归的累加两个子树的查询结果
*/
LL query(int u,int l,int r)
{
    if(tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL sum = 0;
    if(l <= mid) sum += query(u << 1,l,r);
    if(r > mid) sum += query(u << 1 | 1,l,r);
    return sum;
}


int main()
{
    fast_cin();
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> a[i];
    build(1,1,n);
    string op;
    int l,r,d;
    while(m--)  
    {
        cin >> op >> l >> r;
        if(op == "C") 
        {
            cin >> d;
            modify(1,l,r,d);
        }
        else
        {
            // cout << l << ' ' << r << "-->";
            cout << query(1,l,r) << endl;
        }
    }
    return 0;
}