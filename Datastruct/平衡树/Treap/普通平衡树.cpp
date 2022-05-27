#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, INF = 1e8;

int n, op, x;

int idx, root;

struct Node
{
    int l, r;      // 子节点
    int size, cnt; // 当前节点下总共的节点，当前节点重复的个数
    int key, val;  // key是用来BST的值，val是一个随机值，用来做一个期望平衡
} tr[N];

void push_up(int u)
{
    tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + tr[u].cnt;
}

int new_node(int key)
{
    tr[++idx].key = key;
    tr[idx].val = rand(); // 随机排一个
    tr[idx].cnt = tr[idx].size = 1;
    return idx;
}

void right_rotate(int &p)
{ // 画图就很清晰，注意pushup先更新底下的再更新上面的
    int q = tr[p].l;
    tr[p].l = tr[q].r, tr[q].r = p, p = q;
    push_up(tr[p].r), push_up(p);
}

void left_rotate(int &p)
{
    int q = tr[p].r;
    tr[p].r = tr[q].l, tr[q].l = p, p = q;
    push_up(tr[p].l), push_up(p);
}

void build()
{
    new_node(-INF), new_node(INF); // 哨兵节点
    root = 1, tr[root].r = 2;
    push_up(root);

    if (tr[1].val < tr[2].val)
        left_rotate(root);
}

void insert(int &p, int key)
{ // 递归的插入，注意判断val的值之后旋转
    if (!p)
        p = new_node(key);
    else if (tr[p].key == key)
        tr[p].cnt++;
    else if (tr[p].key > key)
    {
        insert(tr[p].l, key); // 新加入的节点val更大的话需要递归的旋转
        if (tr[tr[p].l].val > tr[p].val)
            right_rotate(p);
    }
    else
    {
        insert(tr[p].r, key);
        if (tr[tr[p].r].val > tr[p].val)
            left_rotate(p);
    }
    push_up(p);
}

void del(int &p, int key)
{ // 子节点就直接删除，不是子节点就把他旋转到子节点之后删除
    if (!p)
        return;
    if (tr[p].key == key)
    {
        if (tr[p].cnt > 1)
            tr[p].cnt--;
        else if (tr[p].l || tr[p].r) // 不是叶子节点
        {
            if (!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val)
            { // 可以右旋的情况，没有右儿子或者左儿子的val更大，可以做爹
                right_rotate(p);
                del(tr[p].r, key);
            }
            else
            {
                left_rotate(p);
                del(tr[p].l, key);
            }
        }
        else
            p = 0; // 叶子节点直接删除
    }
    else if (tr[p].key > key)
        del(tr[p].l, key);
    else
        del(tr[p].r, key);
    push_up(p);
}

int get_rank(int p, int key)
{
    if (!p)
        return 0;
    if (tr[p].key == key)
        return tr[tr[p].l].size + 1;
    if (tr[p].key > key)
        return get_rank(tr[p].l, key);
    return tr[tr[p].l].size + tr[p].cnt + get_rank(tr[p].r, key);
}

int get_key(int p, int rank)
{
    if (!p)
        return INF;
    if (tr[tr[p].l].size >= rank)
        return get_key(tr[p].l, rank);
    if (tr[tr[p].l].size + tr[p].cnt >= rank)
        return tr[p].key;
    return get_key(tr[p].r, rank - tr[p].cnt - tr[tr[p].l].size);
}

int get_pre(int p, int key)
{ // 小于key的最大数
    if (!p)
        return -INF;
    if (tr[p].key >= key)
        return get_pre(tr[p].l, key);
    return max(tr[p].key, get_pre(tr[p].r, key));
}

int get_ne(int p, int key)
{ // 大于key的最小数
    if (!p)
        return INF;
    if (tr[p].key <= key)
        return get_ne(tr[p].r, key);
    return min(tr[p].key, get_ne(tr[p].l, key));
}

int main()
{
    cin >> n;
    build(); // 构建Treap，哨兵节点加入
    while (n--)
    {
        cin >> op >> x;
        if (op == 1)
            insert(root, x);
        else if (op == 2)
            del(root, x);
        else if (op == 3)
            cout << get_rank(root, x) - 1 << endl;
        else if (op == 4)
            cout << get_key(root, x + 1) << endl;
        else if (op == 5)
            cout << get_pre(root, x) << endl;
        else
            cout << get_ne(root, x) << endl;
    }
    return 0;
}