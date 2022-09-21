## IDA*

等价于迭代加深 + 启发式。相较于A*，它不需要用优先队列，不需要判重。

空间的需求更少，深度有限制

```
int f() {
  // 启发式函数判断重点距离
}

bool dfs(...,int dep) {
  if(!dep) return judgesucess()
  if(f() > dep) return false
  for x in range(edges) {
    if(dfs(...,dep - 1)) return true;
  }
  return false;
}

int main() {
  int dep = 1;
  while(!dfs(...,dep)) dep++;
  cout << dep << '\n';
  return 0;
}

```


