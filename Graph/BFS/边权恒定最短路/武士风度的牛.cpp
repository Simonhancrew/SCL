#include <iostream>
#include <cstring>

using namespace std;

/*
    确定走的方向
*/ 

typedef pair<int,int> PII;
#define x first
#define y second

const int N = 155,M = N * N;

int n,m;
char g[N][N];
PII q[M];
int dist[N][N];
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int bfs(int x,int y){
    int hh = 0,tt = 0;
    q[0] = {x,y};
    memset(dist, -1, sizeof dist);
    dist[x][y] = 0;
    while(hh <= tt){
        PII t = q[hh++];
        for(int i = 0;i < 8;i++){
            int nx = t.x + dx[i],ny = t.y + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(g[nx][ny] == '*') continue;
            if(dist[nx][ny] != -1) continue;
            if(g[nx][ny] == 'H') return dist[t.x][t.y] + 1;
            dist[nx][ny] = dist[t.x][t.y] + 1;
            q[++tt] = {nx,ny};
        }
    }
    return -1;
}

int main(){
    cin >> m >> n;
    for(int i = 0;i < n;i++) cin >> g[i];
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(g[i][j] == 'K') cout << bfs(i,j) << endl;
        }
    }
    return 0;
}