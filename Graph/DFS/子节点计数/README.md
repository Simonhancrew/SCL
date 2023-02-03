### 节点计数类dfs

1. 利用dfs统计子节点问题, 针对节点

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



