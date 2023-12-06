# 节点计数类dfs

## 利用dfs统计子节点问题, 针对节点

```
int up[N], lhs[N], rhs[N];
int dfs(TreeNode* node, int tar) {
  if (!node) return 0;
  if (node->val == tar) {
    int l = dfs(node->left);
    int r = dfs(node->right);
    // 在这里做相关统计, 上面和左右子树
    up[node->id] = (total - l - r - 1);
    lhs[node->id] = l;
    rhs[node->id] = r;
    return l + r + 1;
  }
  return dfs(node->left, tar) + dfs(node->right, tar) + 1;
}

```

## 节点花费计数问题

1. 上行边代价计算，这种题目一般告诉你汇聚到根，求到根的代价

    ```cpp
    function<int(int, int)> dfs = [&](int x, int fa) {
      int size = 1;
      for (const auto y : g[x]) {
        if (y == fa)
          continue;
        size += dfs(y, x);
      }
      if (x != 0) {
        ans += cost(size); // 计算上行边花费代价
      }
      return size;
    };
    ```

2. 节点花费计算， 类似上面，但是是看节点的花费，一般题目会告诉你是一条联通路径的代价，代码类似，但不用算根，只要知道一条确定路径就可以了

    ```cpp
      int total_cost = 0;
      function<bool(int, int, int)> dfs = [&](int x, int end, int fa) {
        if (x == end) {
          cnt[x]++;
          total_cost += cost(x);
          return true;
        }
        for (const auto y : g[x]) {
          if (y != fa && dfs(y, end, x)) {
            cnt[x]++;
            total_cost += cost(x);
            return true;
          }
        }
        return false;
      };
    ```
