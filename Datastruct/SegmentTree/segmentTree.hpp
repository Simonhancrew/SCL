#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  动态开点的两种写法，第一种是要估计点数的
  第二种直接new开点
*/

#ifdef ALLOC_ALL

// 这里写的是区间重复覆盖的最大次数,不是对每个线段做整体+

const int N = 1e6 + 10;
int cnt = 1;

struct Node
{
    // 左右儿子 + 当前要求的值 + lazy_tag
    int ls,rs,val,tag;
    int l,r;
    Node() {
        l = r = rs = ls = val = tag = 0;
    }
    Node(int l,int r): l(l),r(r),ls(0),rs(0),val(0),tag(0) { }
};

Node tr[N];

void lazy_create(int u) {
    int mid = tr[u].l + tr[u].r >> 1;
    if(tr[u].ls == 0) {
        tr[u].ls = ++cnt;
        tr[tr[u].ls].l = tr[u].l;
        tr[tr[u].ls].r = mid;
    }
    if(tr[u].rs == 0) {
        tr[u].rs = ++cnt;
        tr[tr[u].rs].l = mid + 1;
        tr[tr[u].rs].r = tr[u].r;
    }
}

void push_down(int u) {
    if(tr[u].tag) {
        int &tag = tr[u].tag;
        tr[tr[u].ls].val += tag;
        tr[tr[u].rs].val += tag;
        tr[tr[u].ls].tag += tag;
        tr[tr[u].rs].tag += tag;
        tag = 0;
    }
}

void push_up(int u){
    int lhs = tr[u].ls,rhs = tr[u].rs;
    tr[u].val = max(tr[lhs].val, tr[rhs].val);  
}

void add(int u,int L,int R,int k) {
    if(tr[u].l >= L && tr[u].r <= R) {
        tr[u].val += k;
        tr[u].tag += k;
        return;
    }
    lazy_create(u);
    push_down(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if(mid >= L) add(tr[u].ls,L,R,k);
    if(mid < R) add(tr[u].rs,L,R,k);
    push_up(u);
}

int query(int u,int L,int R) {
    if(tr[u].l >= L && tr[u].r <= R) {
        return tr[u].val;
    }
    lazy_create(u);
    push_down(u);
    int mid = tr[u].l + tr[u].r >> 1;
    int ans = 0;
    if(mid >= L) ans = max(ans,query(tr[u].ls,L,R));
    if(mid < R) ans = max(ans,query(tr[u].rs,L,R));
    return ans;
}

#endif 

#ifdef DYNAMIC
class segtree
{
public:
    segtree(int st, int ed) : l(st), r(ed), val(0), tag(0) {}
    void pushdown();
    bool query(int L, int R);
    void pushup();
    void add(int L, int R, int k);
    unique_ptr<segtree> lhs, rhs;
    int l, r;
    int val;
    int tag;
};

void segtree::pushdown()
{
    int mid = l + r >> 1;
    if (!lhs)
        lhs.reset(new segtree(l, mid));
    if (!rhs)
        rhs.reset(new segtree(mid + 1, r));
    if (tag)
    {
        lhs->val += (mid - l + 1) * tag;
        rhs->val += (r - mid) * tag;
        lhs->tag = tag;
        rhs->tag = tag;
        tag = 0;
    }
}

bool segtree::query(int L, int R)
{
    if (l >= L && r <= R)
    {
        return val;
    }
    pushdown();
    int mid = l + r >> 1;
    int flag = 0;
    if (mid >= L)
        flag += lhs->query(L, R);
    if (mid < R)
        flag += rhs->query(L, R);
    return flag;
}

void segtree::pushup()
{
    val = lhs->val + rhs->val;
}

void segtree::add(int L, int R, int k)
{
    if (l >= L && r <= R)
    {
        val += (r - l + 1) * k;
        tag += k;
    }
    else
    {
        pushdown();
        int mid = l + r >> 1;
        if (mid >= L)
            lhs->add(L, R, k);
        if (mid < R)
            rhs->add(L, R, k);
        pushup();
    }
}
#endif
