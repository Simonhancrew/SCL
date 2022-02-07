#include <iostream>
#include <unordered_map>

using namespace std;


/*
    在区间[l,r]中有多少个1可以用前缀和求取，s[r] - s[l - 1]
    这里比较特殊，判断的是奇偶，只要s[r]和s[l-1]同奇偶性就一定能得到偶数个1
    所以可以用并查集做一个合并，将一端看作根节点，另一端往树根合并
    其中用一个带权并查集维护其和根的关系，其中d[x] = 0时表示奇偶性相同
    在没确定两个端点的关系的时候，将其加入并查集
    在确定了关系的时候考虑奇偶性能否满足
*/

const int N = 1e4 + 10;
int n,m,cnt;
int p[N],d[N];
unordered_map<int,int> mp;

int get(int x) {
    if(!mp.count(x)) mp[x] = cnt++;
    return mp[x];
}

int find(int x) {
    if(p[x] != x) {
        int root = find(p[x]);
        d[x] ^= d[p[x]];
        p[x] = root;
    }
    return p[x];
}


int main(){
    cin >> n >> m;
    int res = m;
    for(int i = 0;i < N;i++) p[i] = i;
    for(int i = 0;i < m;i++) {
        string op;
        int a,b;
        cin >> a >> b >> op;
        a = get(a - 1),b = get(b);
        int t = 0;
        if(op == "odd") t = 1;
        int pa = find(a),pb = find(b);
        if(pa == pb) {
            if(d[a] ^ d[b] != t) {
                res = i;
                break;
            }
        }else{
            p[pa] = pb;
            d[pa] = d[a] ^ d[b] ^ t;
        }
    }
    cout << res << endl;
    return 0;
}