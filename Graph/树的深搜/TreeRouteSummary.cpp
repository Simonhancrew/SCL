// 针对从root节点开始的路径类问题
// 不带限制，暴搜所有的路径
vector<vector<int>>res;
void dfs(TreeNode*root,vector<int>path)
{
    if(!root) return;  
    path.push_back(root->val);  
    if(!root->left && !root->right)   
    {
        res.push_back(path);
        return;
    }
    dfs(root->left,path);  
    dfs(root->right,path);
}

// 带值范围限制
void dfs(TreeNode*root, int sum, vector<int> path)
{
    if (!root)
        return;
    sum -= root->val;
    path.push_back(root->val);
    if (!root->left && !root->right && sum == 0)
    {
        res.push_back(path);
        return;
    }
    dfs(root->left, sum, path);
    dfs(root->right, sum, path);
}

// 针对任意节点的直径上求和类问题

int res=0;
int dfs(TreeNode *node) 
{
    if (!node)
        return 0;
    int left=dfs(node->left);
    int right=dfs(node->right);
    res = max(res, left + right + node->val);   
    return max(left, right);  
}



