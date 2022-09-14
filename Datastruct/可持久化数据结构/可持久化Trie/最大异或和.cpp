#include <algorithm>
#include <iostream>

using namespace std;

/*
    1. trie的空间比较限制，如果可能爆的话就开空间限制-10M的空间
    主要操作两个，一个在末尾添加，一个查询[l,r]的中的一个p，令[p,r]的异或和再异或上x的值最小
    求这个值

    本题的基础模板题是最大异或和（不用可持久化trie的）

    先对所有输入的数做一个前缀和s，不难观察到[l,n]的前缀和就是
    s[n] ^ s[l - 1]
    只考虑右边界的话，可以考虑只维护一个持久字典树，考虑左边界的话
    还需要维护一个maxid，在搜索的过程中看当前子树中的最大id是否达到目前的下界
    还需要注意的是，求解[l,r]的一个p,[p,r]的异或和 ^ x最小，但是
    实际的公式是s[n] ^ s[p - 1] ^ x
    则实际求这个p - 1的范围就是[l - 1,r - 1]
    所以l =
   1也可以是一个可行解,所以可持久trie也需要维护0这一个解（s[0]也是一个合法解）
*/

#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

/*
    数据范围1e7,大概是pow(2,24),每次更新最多添加24个节点加上根节点
*/
const int N = 6e5 + 10, M = N * 25;

int s[N];
int tr[M][2], max_id[M];
int root[N], idx;
int n, m;

// 递归，当前插入数的s[i],二进制位u,前一个版本的根pre,当前版本的根cur
void insert(int id, int u, int pre, int cur) {
  if (u < 0) {
    max_id[cur] = id;
    return;
  }
  int v = s[id] >> u & 1;
  if (pre) tr[cur][v ^ 1] = tr[pre][v ^ 1];
  tr[cur][v] = ++idx;
  insert(id, u - 1, tr[pre][v], tr[cur][v]);
  max_id[cur] = max(max_id[tr[cur][0]], max_id[tr[cur][1]]);
}

void insert(int id, int pre, int cur) {
  max_id[cur] = id;
  for (int i = 23; i >= 0; i--) {
    int v = s[id] >> i & 1;
    if (pre) tr[cur][v ^ 1] = tr[pre][v ^ 1];  // 另外一半继承原版本就可以了
    tr[cur][v] = ++idx;
    max_id[tr[cur][v]] = id;
    pre = tr[pre][v], cur = tr[cur][v];
  }
}

int query(int root, int sum, int limit) {
  for (int i = 23; i >= 0; i--) {
    int v = sum >> i & 1;
    if (max_id[tr[root][v ^ 1]] >= limit)
      root = tr[root][v ^ 1];
    else
      root = tr[root][v];
  }
  return sum ^ s[max_id[root]];  // 叶子节点的max_id就是本身是那个s[i]
}

int main() {
  fast_cin();
  cin >> n >> m;

  root[0] = ++idx;
  /*
      因为要往子树找，最小是0
      但是这个实际是不应该进入的
      搞一个比最还小的就行了
  */
  max_id[0] = -1;
  insert(0, 0, root[0]);

  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    s[i] = s[i - 1] ^ x;
    root[i] = ++idx;
    insert(i, root[i - 1], root[i]);
  }
  int l, r, x;
  string op;
  while (m--) {
    cin >> op;
    if (op == "A") {
      cin >> x;
      n++;
      root[n] = ++idx;
      s[n] = s[n - 1] ^ x;
      insert(n, root[n - 1], root[n]);
    } else {
      cin >> l >> r >> x;
      cout << query(root[r - 1], s[n] ^ x, l - 1) << endl;
    }
  }
  return 0;
}