#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e3 + 10,M = N * N;

/*
    BFS求最短路的时候，对头的一定是一个最小值，具有单调性(队列中的值)
    所以只要初始化全-1就可以
    针对多源BFS，只要将初始的起点dist都设为0，放入队列中做一次更新就可以了
*/

typedef pair<int, int> PII;
#define x first
#define y second
#define fast_cin() ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)

int n,m;
char g[N][N];
int dist[N][N];
PII q[M];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

void bfs(){
    int hh = 0,tt = -1;
    memset(dist,-1,sizeof dist);
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++){
            if(g[i][j] == '1') {
                q[++tt] = {i,j};
                dist[i][j] = 0;
            }
        }
    }
    while(hh <= tt) {
        PII t = q[hh++];
        for(int i = 0;i < 4;i++){
            int nx = t.x + dx[i],ny = t.y + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[t.x][t.y] + 1;
            q[++tt] = {nx,ny};
        }
    }
}

int main(){
    fast_cin();
    cin >> n >> m;
    for(int i = 0;i < n;i++) cin >> g[i];
    bfs();
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}