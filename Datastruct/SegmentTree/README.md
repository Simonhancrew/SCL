## Segment Tree

线段树是一种用于维护区间信息的数据结构，可以在log(n)的时间复杂度下实现单点修改，区间修改，区间查询（区间和，区间最值）等操作

线段树将每个长度不为1的区间划分成左右两个区间递归求解，把整个线段划分为一个树形结构，通过合并左右两区间信息来求得该区间的信息。这种数据结构可以方便的进行大部分的区间操作。


建树操作可以递归的进行，一个自底向上的操作，更新完底部节点之后需要更新父节点的值，线段树的根节点编号是1的话，d[i]用于保存树上编号值为i节点的值

```cpp
void build(int s, int t, int p) {
  // 对 [s,t] 区间建立线段树,当前根的编号为 p
  if (s == t) {
    d[p] = a[s];
    return;
  }
  int m = s + ((t - s) >> 1);
  build(s, m, p * 2), build(m + 1, t, p * 2 + 1);
  // 子节点更新结束，更新当前节点值
  d[p] = d[p * 2] + d[(p * 2) + 1];
}
```

如果要查询一段区间的和,则可以将其拆成最多为O(logn)的区间（树高），合并这些区间就可以得到答案
```cpp
int getsum(int l, int r, int s, int t, int p) {
  // [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p 为当前节点的编号
  if (l <= s && t <= r)
    return d[p];  // 当前区间为询问区间的子集时直接返回当前区间的和
  int m = s + ((t - s) >> 1), sum = 0;
  if (l <= m) sum += getsum(l, r, s, m, p * 2);
  // 如果左儿子代表的区间 [l, m] 与询问区间有交集, 则递归查询左儿子
  if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
  // 如果右儿子代表的区间 [m + 1, r] 与询问区间有交集, 则递归查询右儿子
  return sum;
}
```

区间修改的时候，当需要区间分裂的时候一定记得把lazy tag往下传，通过延迟对节点信息的更改，从而减少可能不必要的操作次数。

当达到一个节点，这个节点的左右端点完全包含在需要修改的范围内的时候，就没有必要继续下去了(类似到达了一个叶子节点)，这个时候可以记一个todo的tag，当要后面继续要走下的的时候，需要把这个todo的操作继续下去。

这个修改操作也是递归的，即自底向上，所以在对子节点完成修改之后，需要通知父节点完成修改。

```cpp
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

// modify和query中的l和r是要修改和查询的区间，是个常量
void modify(int u,int kL,int kR,int d)
{
    if(tr[u].l >= kL && tr[u].r <= kR)
    {
        tr[u].sum += (LL)(tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
    }
    else
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(kL <= mid) modify(u << 1, kL, kR, d);
        if(kR > mid) modify(u << 1 | 1, kL, kR, d);
        pushup(u);
    }
}

LL query(int u,int kL,int kR)
{
    if(tr[u].l >= kL && tr[u].r <= kR) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL sum = 0;
    if(l <= mid) sum += query(u << 1,kL,kR);
    if(r > mid) sum += query(u << 1 | 1,kL,kR);
    return sum;
}
```


最后有一个关于seg tree的优化,在叶子节点处无需下放懒标记，所以懒标记可以不下传到叶子节点。

## 动态开点线段树

左右儿子此时不再用u << 1和u << 1 | 1代表，而是用ls和rs记录左右儿子的编号。

比起普通线段树，动态开点线段树有一个优势：它能够处理零或负数位置。此时，求mid时不能用(cl+cr)/2，而要用(cl+cr-1)/2。push_down因此也要相应改一下。

```cpp
// MAXV一般能开多大开多大，例如内存限制128M时可以开到八百万左右
#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
#define val(x) tree[x].val
#define mark(x) tree[x].mark
const int MAXV = 8e6;
int L = 1, R = 1e5, cnt = 1;
struct node
{
    ll val, mark;
    int ls, rs;
} tree[MAXV];
void push_down(int p, int len)
{
    if (len <= 1) return;
    if (!ls(p)) ls(p) = ++cnt;
    if (!rs(p)) rs(p) = ++cnt;
    val(ls(p)) += mark(p) * (len / 2);
    mark(ls(p)) += mark(p);
    val(rs(p)) += mark(p) * (len - len / 2);
    mark(rs(p)) += mark(p);
    mark(p) = 0;
}

//cl,cr是查询区间常量，l,r是当前节点左右
ll query(int l, int r, int p = 1, int cl = L, int cr = R) 
{
    if (cl >= l && cr <= r) return val(p);
    push_down(p, cr - cl + 1);
    ll mid = (cl + cr - 1) / 2, ans = 0;
    if (mid >= l) ans += query(l, r, ls(p), cl, mid);
    if (mid < r) ans += query(l, r, rs(p), mid + 1, cr);
    return ans;
}
void update(int l, int r, int d, int p = 1, int cl = L, int cr = R)
{
    if (cl >= l && cr <= r) return val(p) += d * (cr - cl + 1), mark(p) += d, void();
    push_down(p, cr - cl + 1);
    int mid = (cl + cr - 1) / 2;
    if (mid >= l) update(l, r, d, ls(p), cl, mid);
    if (mid < r) update(l, r, d, rs(p), mid + 1, cr);
    val(p) = val(ls(p)) + val(rs(p));
}
```
