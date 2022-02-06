#include <iostream>

using namespace std;

/*
    简单并查集，合并节点，知道可能成环的时候结束
*/ 

const int N = 4e4 + 10;

int n,m;
int p[N];

void init(){
    for(int i = 0;i < n * n;i++) p[i] = i;
}

int find(int x) {
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int get(int x,int y) {
    return x * n + y;
}

int main(){
    cin >> n >> m;
    init();
    int res = 0;
    for(int i = 1;i <= m;i++) {
        int x,y;
        char d;
        cin >> x >> y >> d;
        --x,--y;
        int a = get(x,y),b;
        if(d =='D') b = get(x + 1,y);
        else b = get(x,y + 1);
        int pa = find(a),pb = find(b);
        if(pa == pb) {
            res = i;
            break;
        }
        p[pa] = pb;
    }
    if(!res) cout << "draw" << endl;
    else cout << res << endl;
    return 0;
}