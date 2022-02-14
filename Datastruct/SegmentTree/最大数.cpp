#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/02/13

using namespace std;

typedef long long LL;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int N = 2e5 + 10;

int m,p;

/*
    倒数第二层假设n,上方n - 1,下方最多2 * n,总共最多
    4 * n - 1
*/ 
struct Node{
    int l,r;
    int v; // 区间[l,r]的最大值
}tr[N * 4];

/*
    一个建树的过程，区间端点相等的时候说明到了叶节点
    直接返回即可，否则递归的建树，父节点是u的话
    左儿子就是u * 2，右儿子就是u * 2  + 1
*/
void build(int u,int l,int r)
{
    tr[u] = {l,r};
    if(l == r) return;
    int mid = l + r >> 1;
    build(u << 1,l,mid),build(u << 1 | 1,mid + 1,r);
}

/*
    父节点更新左右子树的过程
*/
void push_up(int u)
{
    tr[u].v = max(tr[u << 1].v,tr[u << 1 | 1].v);
}

/*
    查询的区间在递归过程中是不动的，方便看某次是否完全包含
*/
int query(int u,int l,int r) 
{
    if(tr[u].l >= l && tr[u].r <= r) return tr[u].v; // 已经完全被包含，没必要往下走了。
    
    int mid = tr[u].l + tr[u].r >> 1;
    int v = 0;
    if(l <= mid) v = query(u << 1,l,r);
    if(r > mid) v = max(v,query(u << 1 | 1,l,r));
    
    return v;
}

/*
    有儿子的节点才push_up,在节点x处修改v
*/
void modify(int u,int x,int v)
{
    if(tr[u].l == x && tr[u].r == x) tr[u].v = v;
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if(x <= mid) modify(u << 1,x,v);
        else modify(u << 1 | 1,x,v);
        push_up(u);
    }
}

int main()
{
    fast_cin();
    int last = 0,n = 0,x; // n是当前动态区间的右端点
    string op;
    cin >> m >> p;
    build(1,1,m);
    while(m--) 
    {
        cin >> op >> x;
        if(op == "Q") 
        {
            last = query(1,n - x + 1,n);
            cout << last << '\n';
        }
        else
        {
            modify(1,n + 1,((LL)last + x) % p);
            n++;
        }
    }
    return 0;
}