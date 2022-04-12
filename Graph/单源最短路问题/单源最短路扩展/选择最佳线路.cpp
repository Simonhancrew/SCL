#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

// Created by Simonhancrew on 2022/04/12

using namespace std;

/*
    其实思路和多源BFS类似，但此处新建了一个超级原点
    将超级原点和可行起点连接，随后求终点的最短路
    因为增加超级原点和可行起点的边，所以实际的边要开大一点
    最短路可用dji和spfa
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e3 + 10, M = 2e4 + 10 + 1000;

int h[N], e[M], ne[M], w[M], idx;
int dist[N];
bool st[N];
queue<int> q;
int n, m, s;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;
    st[0] = true;
    q.push(0);
    while (q.size())
    {
        auto t = q.front();
        q.pop();
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])
                {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }
    if (dist[s] == INF)
        return -1;
    return dist[s];
}

int main()
{
    fast_cin();
    while (cin >> n >> m >> s)
    {
        idx = 0;
        memset(h, -1, sizeof h);
        while (m--)
        {
            int a, b, c;
            cin >> a >> b >> c;
            add(a, b, c);
        }
        int w;
        cin >> w;
        while (w--)
        {
            int a;
            cin >> a;
            add(0, a, 0);
        }
        int res = spfa();
        cout << res << endl;
    }
    return 0;
}

/*
package main


import(
    "os"
    "bufio"
    ."fmt"
)

const (
    N = 1e3 + 10
    M = 2e4 + 10 + 1000
    INF = 0x3f3f3f3f
)

var m,n,s,idx int
var h,dist [N]int
var e,ne,w [M]int
var st [N]bool

func add(a,b,c int) {
    e[idx],w[idx],ne[idx] = b,c,h[a]
    h[a] = idx
    idx++
}

func spfa() int {
    for i := 0;i <= n;i++ {
        dist[i] = INF
    }
    dist[0] = 0
    st[0] = true
    q := make([]int,n + 1)
    q[0] = 0
    hh,tt := 0,1
    for hh != tt {
        t := q[hh]
        hh++
        if hh == n {
            hh = 0
        }
        st[t] = false
        for i := h[t];i != -1;i = ne[i] {
            j := e[i]
            if dist[j] > dist[t] + w[i] {
                dist[j] = dist[t] + w[i]
                if !st[j] {
                    st[j] = true
                    q[tt] = j
                    tt++
                    if tt == n {
                        tt = 0
                    }
                }
            }
        }
    }
    if dist[s] == INF {
        return -1
    }
    return dist[s]
}

func main() {
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()

    for  {
        _,ok := Fscan(in,&n,&m,&s)
        if ok != nil {
            break
        }
        idx = 0
        for i := 0;i <= n;i++ {
            h[i] = -1
        }
        for i := 0;i < m;i++ {
            var a,b,c int
            Fscan(in,&a,&b,&c)
            add(a,b,c)
        }
        var w int
        Fscan(in,&w)
        for i := 0;i < w;i++ {
            var t int
            Fscan(in,&t)
            add(0,t,0)
        }

        res := spfa()
        Fprintln(out,res)
    }
}
*/