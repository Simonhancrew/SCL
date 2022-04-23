#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

// Created by Simonhancrew on 2022/04/23, Leetcode-587

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

int cross(int x1, int y1, int x2, int y2)
{
    return x1 * y2 - x2 * y1;
}

int area(vector<int> &a, vector<int> &b, vector<int> &c)
{
    return cross(b[0] - a[0], b[1] - a[1], c[0] - a[0], c[1] - a[1]);
}

int main()
{
    fast_cin();
    string s;
    cin >> s;
    vector<vector<int>> trees;
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '[' || s[i] == ',' || s[i] == ']')
            continue;
        vector<int> cur;
        int j = i;
        while (j < n && s[j] != ',')
            j++;
        cur.push_back(stoi(s.substr(i, j - i)));
        i = j + 1;
        while (j < n && s[j] != ']')
            j++;
        cur.push_back(stoi(s.substr(i, j - i)));
        i = j;
        trees.push_back(cur);
    }
    sort(trees.begin(), trees.end());
    vector<int> used(n + 1), pt(n + 2);
    int top = 1;
    pt[top] = 0;
    n = trees.size();
    for (int i = 1; i < n; i++)
    {
        // 只要不是左拐就行，可以直线更新，<=0都可以
        while (top >= 2 && area(trees[pt[top - 1]], trees[pt[top]], trees[i]) > 0)
        {
            used[pt[top]] = false;
            top--;
        }
        used[i] = true;
        pt[++top] = i;
    }
    used[0] = false;
    int tmp = top;
    for (int i = n - 1; i >= 0; i--)
    {
        if (used[i])
            continue;
        while (top > tmp && area(trees[pt[top - 1]], trees[pt[top]], trees[i]) > 0)
        {
            used[pt[top]] = false;
            top--;
        }
        used[i] = true;
        pt[++top] = i;
    }
    top--;
    for (int i = 1; i <= top; i++)
    {
        cout << trees[pt[i]][0] << ' ' << trees[pt[i]][1] << endl;
    }
    return 0;
}