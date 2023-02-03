#include <functional>
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// from lc 1145, x可以把一个树分成三部分， 左右子树和上面的部分
// 分别计算整体的size就可以了
class Solution {
public:
  bool btreeGameWinningMove(TreeNode* root, int n, int x) {
    int ans = 0;
    function<int(TreeNode* node)> dfs = [&](TreeNode* node) {
      if (!node) return 0;
      if (node->val == x) {
        int l = dfs(node->left);
        int r = dfs(node->right);
        ans = max({ans, l, r, n - l - r - 1});
        return l + r + 1;
      } 
      return dfs(node->left) + dfs(node->right) + 1;
    };
    dfs(root);
    return ans > n - ans;
  }
};

