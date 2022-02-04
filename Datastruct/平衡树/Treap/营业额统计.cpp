#include <iostream>
#include <algorithm>

using namespace std;

const int N = 33000,INF = 0x3f3f3f3f;

typedef long long LL;

struct Node{
    int l,r;
    int val,key;
}tr[N];

int n,t;
int root,idx;

int new_node(int key) { // 记得返回指针！！！！！
    tr[++idx].key = key;
    tr[idx].val = rand();
    return idx;
}

void left_rotate(int &p) {
    int q = tr[p].r;
    tr[p].r = tr[q].l,tr[q].l = p,p = q;
}

void right_rotate(int &p) {
    int q = tr[p].l;
    tr[p].l = tr[q].r,tr[q].r = p,p = q;
}

void build() {
    new_node(-INF),new_node(INF);
    root = 1,tr[1].r = 2;
    if(tr[1].val < tr[2].val) left_rotate(root);
}

void insert(int &p,int key) {
    if(!p) p = new_node(key);
    else if(tr[p].key == key) return;
    else if(tr[p].key > key) 
    {
        insert(tr[p].l,key);
        if(tr[tr[p].l].val > tr[p].val) right_rotate(p);
    }
    else 
    {
        insert(tr[p].r,key);
        if(tr[tr[p].r].val > tr[p].val) left_rotate(p);
    }
}

int get_pre(int p,int key) {
    if(!p) return -INF;
    if(tr[p].key > key) return get_pre(tr[p].l,key);
    return max(tr[p].key,get_pre(tr[p].r,key));
}

int get_ne(int p,int key) {
    if(!p) return INF;
    if(tr[p].key < key) return get_ne(tr[p].r,key);
    return min(tr[p].key,get_ne(tr[p].l,key));
}

int main(){
    cin >> n;
    build();
    LL res = 0;
    for(int i = 1;i <= n;i++) {
        cin >> t;
        if(i == 1) res += t;
        else res += min(t - get_pre(root,t),get_ne(root,t) - t);
        insert(root,t);
    }
    cout << res << endl;
    return 0;
}