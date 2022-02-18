## Segment Tree

线段树是一种用于维护区间信息的数据结构，可以在log(n)的时间复杂度下实现单点修改，区间修改，区间查询（区间和，区间最值）等操作

线段树将每个长度不为1的区间划分成左右两个区间递归求解，把整个线段划分为一个树形结构，通过合并左右两区间信息来求得该区间的信息。这种数据结构可以方便的进行大部分的区间操作。


建树操作可以递归的进行，线段树的根节点编号是1的话，d[i]用于保存树上编号值为i节点的值

```cpp
void build(int s, int t, int p) {
  // 对 [s,t] 区间建立线段树,当前根的编号为 p
  if (s == t) {
    d[p] = a[s];
    return;
  }
  int m = s + ((t - s) >> 1);
  // 移位运算符的优先级小于加减法，所以加上括号
  // 如果写成 (s + t) >> 1 可能会超出 int 范围
  build(s, m, p * 2), build(m + 1, t, p * 2 + 1);
  // 递归对左右区间建树
  d[p] = d[p * 2] + d[(p * 2) + 1];
}
```

如果要查询一段区间的和,则可以将其拆成最多为O(logn)的区间，合并这些区间就可以得到答案
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

区间修改的时候，当需要区间分裂的时候一定记得把lazy tag往下传，通过延迟对节点信息的更改，从而减少可能不必要的操作次数。当区间修改的时候，一次最多修改[l,r]全部的节点，这个复杂度是无法接受的。通过打标记的方法表明该节点对应的区间在某一次操作中被更改，但不更新该节点的子节点的信息。实质性的修改则在下一次访问带有标记的节点时才进行

需要注意的是，在当前节点不下沉的时候，当前节点记录的值一定是正确的，如果要分裂的话，一定要下沉，先要传递懒标记

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
```


最后有一个关于seg tree的优化,在叶子节点处无需下放懒标记，所以懒标记可以不下传到叶子节点。

