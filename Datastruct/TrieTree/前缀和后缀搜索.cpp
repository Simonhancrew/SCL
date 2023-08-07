#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

// Created by Simonhancrew on 2022/07/14

using namespace std;

/*
    在给出的单词表中，找到具有给出前后缀的单词。如果又多个，按照单词表的
    下标给出最大的。
    想到字典树比较简单，在做的过程中，如果不想开两颗字典树的话
    可以在插入过程中存s[n..0] + "#" + s的信息。字典树记录当前节点走到的最大id
    比如ab，就应该往字典树中插入ab,#ab,b#ab,ab#ab.这样在满足要求的时候一定能找到这个值
    且如果后续的words中有合法的，id一定会被覆盖。
    当某次查询到合法值是，id一定是最大下标
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 4e5 + 10;

int n;
int son[N][27], idx;
int w[N];

void insert(string s, int id)
{
    int p = 0;
    for (auto c : s)
    {
        int t = c == '#' ? 26 : c - 'a';
        if (!son[p][t])
            son[p][t] = ++idx;
        p = son[p][t];
        w[p] = id;
    }
}

int query(string s)
{
    int p = 0;
    for (auto c : s)
    {
        int t = c == '#' ? 26 : c - 'a';
        if (!son[p][t])
            return -1;
        p = son[p][t];
    }
    return w[p];
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    fast_cin();
    cin >> n;
    vector<string> words;
    for (int i = 0; i < n; i++)
    {
        string word;
        cin >> word;
        words.push_back(word);
    }

    for (int i = 0; i < n; i++)
    {
        string s = "#" + words[i];
        insert(s, i);
        for (int j = words[i].size() - 1; j >= 0; j--)
        {
            s = words[i][j] + s;
            insert(s, i);
        }
    }

    string prefix, suffix;
    cin >> prefix >> suffix;

    cout << query(suffix + "#" + prefix) << '\n';
    return 0;
}