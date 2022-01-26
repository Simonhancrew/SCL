#include <iostream>
#include <cstring>
#include <deque>

using namespace std;

typedef pair<int,int> PII;

/*
    只有\能走，/是要扭转的。可以抽象成一个最短路问题，/的边权是1
    \的边权是0.这类最短路可以不用dij，直接做一个双端队列BFS
    同理依然存在一个冗余的问题，出队的时候要做一个判断
    双端队列BFS时，头部保证能够最小，因为0权基本就是距离不变，
    往头部加，距离变大的往尾部加，模拟了一个堆，但是时线性的
*/

const int N = 510;

typedef pair<int, int> PII;
#define x first
#define y second

int t;
int n,m;
int dist[N][N];
bool st[N][N];
char g[N][N];
int dx[4] = {-1,-1,1,1},dy[4] = {-1,1,1,-1};
int ix[4] = {-1,-1,0,0},iy[4] = {-1,0,0,-1};


int bfs() {
    memset(dist,0x3f,sizeof dist);
    memset(st,0,sizeof st);
    string dir = "\\/\\/"; // 转意
    deque<PII> q;
    dist[0][0] = 0;
    q.push_back({0,0});
    while(q.size()) {
        auto t = q.front();
        q.pop_front();
        int x = t.x,y = t.y;
        if(st[x][y]) continue;
        st[x][y] = 1;
        for(int i = 0;i < 4;i++) {
            int nx = x + dx[i],ny = y + dy[i];
            if(nx < 0 || nx > n || ny < 0 || ny > m) continue;
            int cx = x + ix[i],cy = y + iy[i];
            int w = (g[cx][cy] != dir[i]);
            int nd = dist[x][y] + w;
            if(nd < dist[nx][ny]) {
                dist[nx][ny] = nd;
                if(w) q.push_back({nx,ny});
                else q.push_front({nx,ny});
            }
        }
    }
    return dist[n][m];
}

int main(){
    cin >> t;
    while(t--) {
        cin >> n >> m;
        for(int i = 0;i < n;i++) cin >> g[i];
        int ans = bfs();
        if(ans == 0x3f3f3f3f) cout << "NO SOLUTION" << endl;
        else cout << ans << endl;
    }
    return 0;
}