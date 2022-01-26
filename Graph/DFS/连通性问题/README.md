## 连通性问题

主要考虑连通性判断和连通区域的点数

另外一个就是回溯的问题，区域搜索是不需要的，这里不像棋盘问题，需要考虑多个分支时刻的期盼状态，遍历之后不需要恢复原状态。只需要做一个判重


### 连通性判断
```
bool dfs(int x,int y) {
    if(end) return true;
    for(4 directions) {
        if(dfs(nx,ny)) return true;
    }
    return false;
}
```

### 连通区大小

```
int dfs(int x,int y) {
    int cnt = 1;
    for(4 directions) {
        cnt += dfs(nx,ny);
    }
    return cnt;
}
```




