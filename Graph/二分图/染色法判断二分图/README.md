## 染色法

处理的方法很简单，在DFS（BFS）的过程中给点染色。相邻的点不能染成同色，出现矛盾说明不是二分图

```cpp
int color[N]; // 0还没染色，1染成白色，2染成黑色
bool dfs(int u,int c){
    //先给当前点染色
    color[u] = c;
    //遍历周围的点
    for(int i = h[u];i != -1;i = ne[i]){
        int j = e[i];
        //没染色就去染色深搜，过程中有矛盾情况直接判错
        if(!color[j]){
            bool t = dfs(j,3 - c);
            if(!t) return false;
        }else if(color[j] == c){
            return false;
        }
    }
    return true;
}
```