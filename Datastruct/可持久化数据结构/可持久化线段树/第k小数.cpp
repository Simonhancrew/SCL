#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define fast_cin() ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

/*
    1. 给出的值区间较大，需要离散化
    2. 线段树存区间中的数有多少个，l,r指向子树。线段树总体的区间长度是一直不变的
    3. 针对[l,r],可以考虑一个前缀和的思路。tr[r].cnt - tr[l - 1].cnt
    就是当前[l,r]区间中数的个数，只要找到第k个是谁就可以了
*/

const int N = 1e5 + 10,M = 1e4 + 10;

int n,m;
int a[N];
vector<int> nums;

/*
    在离散化之后的数值区间中建立线段树，每个区间中有多少个数。
    这个区间的长度是固定的
    l，r不再是坐标值,代表两个子树。当相等的时候代表叶节点
*/ 
struct Node
{
    int l,r; 
    int cnt;
}tr[N * 4 + N * 17]; // 一共添加1e4个操作，最多修改logM次

int root[N],idx;

int find(int x) 
{
    return lower_bound(nums.begin(),nums.end(),x) - nums.begin(); 
}

int build(int l,int r)
{
    int p = ++idx;
    if(l == r) return p;
    int mid = l + r >> 1;
    tr[p].l = build(l,mid),tr[p].r = build(mid + 1,r);
    tr[p].cnt = tr[tr[p].l].cnt + tr[tr[p].r].cnt;
    return p;
}

int insert(int p,int l,int r,int x)
{
    int q = ++idx;// 新树指针
    tr[q] = tr[p];
    if(l == r) 
    {
        tr[q].cnt++;
        return q;
    }
    int mid = l + r >> 1;
    if(x <= mid) tr[q].l = insert(tr[p].l,l,mid,x);
    else tr[q].r = insert(tr[p].r,mid + 1,r,x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
    return q;
}

/*
    考虑有边界，只需要第i个版本的线段树就可以了，只有第r次
    及之前的插入记录。针对左边界，可以考虑tr[l - 1]，
    代表[0,l - 1]的这几次插入中，当前区间的数目个数
    tr[r].cnt - tr[l - 1].cnt就能代表[l,r]区间中数的
    个数，针对第k大的数，找到nums中这个节点就行了
*/
int query(int q,int p,int l,int r,int k)
{
    if(l == r) return r; 
    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
    int mid = l + r >> 1;
    if(k <= cnt) return query(tr[q].l,tr[p].l,l,mid,k);
    return query(tr[q].r,tr[p].r,mid + 1,r,k - cnt);
}


int main()
{
    fast_cin();
    cin >> n >> m;
    for(int i = 1;i <= n;i++) {
        cin >> a[i];
        nums.push_back(a[i]);
    }
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    root[0] = build(0,nums.size() - 1);

    for(int i = 1;i <= n;i++) 
    {
        root[i] = insert(root[i - 1],0,nums.size() - 1,find(a[i]));
    }
    int l,r,k;
    while(m--)
    {
        cin >> l >> r >> k;
        cout << nums[query(root[r],root[l - 1],0,nums.size() - 1,k)] << endl;
    }
    return 0;
}