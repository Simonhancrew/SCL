# 字典树

字典树，用边来表示一个字母，每个结点记录一些信息。从根节点到某个节点的路径，代表了一个字符串。

如果需要记录插入的是那些字符串，只需要在节点上打tag即可.

```
struct trie {
  static const int N = 1e4 + 10;
  int nex[N][26]{}, cnt{};
  bool exist[N]{};  // 该结点结尾的字符串是否存在

  void insert(char *s, int l) {  // 插入字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) nex[p][c] = ++cnt;  // 如果没有，就添加结点
      p = nex[p][c];
    }
    exist[p] = 1;
  }

  bool find(char *s, int l) {  // 查找字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) return 0;
      p = nex[p][c];
    }
    return exist[p];
  }
};
```



