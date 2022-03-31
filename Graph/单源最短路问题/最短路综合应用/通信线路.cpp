#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>

// Created by Simonhancrew on 2022/03/31

using namespace std;

/*
    最大值最小=>二分
    挑选k条免费，剩下的就付一个边权最大的值 => 找这个边界，<=的都需要算钱，
    大于的都放进k条免费的中。
    等价于从1到n中的路径中，边权大于bound的边不超过k条
    只要dist[n] <= k则表明当前解合法
    左右端点：
        l = 0,最短路经过的边总共也不足k的话，直接白嫖了
        r = 1e6 + 1,假设不通,则因为二分还是会返回r原值
        需要做一个区分.权最大是1e6,通的话最大是1e6的花费，只要比这个大救行
    实质上边权大于bound的就算做1，小于等于的0，完全可以用双端队列BFS来
    模拟堆优化的dij
*/

typedef long long LL;
typedef pair<int,int> PII;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int INF = 0x3f3f3f3f,N = 1e3 + 10,M = 2e4 + 10;

int n,p,k;
int h[N],e[M],ne[M],w[M],idx;
int d[N];
bool st[N];
deque<int> heap;

void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}

bool check(int bound) {
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    d[1] = 0;
    heap.push_back(1);
    while(heap.size()) 
    {
        auto t = heap.front();
        heap.pop_front();
        if(st[t]) continue;
        st[t] = true;
        for(int i = h[t];i != -1;i = ne[i]){
            int j = e[i],dis = w[i] > bound;
            if(d[j] > d[t] + dis) {
                d[j] = d[t] + dis;
                if(!dis) heap.push_front(j);
                else heap.push_back(j);
            }
        }
    }
    return d[n] <= k;
}


int main(){
    fast_cin();
    cin >> n >> p >> k;
    memset(h,-1,sizeof h);
    for(int i = 0;i < p;i++){
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c),add(b,a,c);
    }
    int l = 0,r = 1e6 + 1;
    while(l < r) {
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    if(r == 1e6 + 1) cout << -1 << endl;
    else cout << r << endl;
    return 0;
}