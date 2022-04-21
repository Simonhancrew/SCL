#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/04/21

using namespace std;

/*
    floyd求解传递闭包，针对原图做最短路变种，此时d[i][j]描述一种关系
    如果d[i][k],d[k][j]连通的话，d[i][j]连通
    针对此类问题的判断：
        1. 如果存在d[i][i] == 1，则表明关系出现了矛盾
        2. 如果每一对的d[i][j],d[j][i]中只有一个是1的，则整体关系得到确定
        3. 剩下的情况均为关系没有得到确定
*/

typedef long long LL;
typedef pair<int, int> PII;

#define PASSCLOSOURES

const int N = 30;

// 传递闭包的做法
#ifdef PASSCLOSOURES
int n, m;
bool g[N][N], d[N][N];
bool st[N];

void floyd()
{
    memcpy(d, g, sizeof g);
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                d[i][j] |= d[i][k] && d[k][j];
            }
        }
    }
}

int check()
{
    for (int i = 0; i < n; i++)
    {
        if (d[i][i])
            return 2;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (!d[i][j] && !d[j][i])
                return 0;
        }
    }

    return 1;
}

char get_min()
{
    for (int i = 0; i < n; i++)
    {
        if (!st[i])
        {
            bool flag = true;
            for (int j = 0; j < n; j++)
            {
                if (!st[j] && d[j][i])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                // 记得标记使用过
                st[i] = true;
                return 'A' + i;
            }
        }
    }
}

int main()
{
    while (cin >> n >> m, n || m)
    {
        int type = 0, t = 0;
        memset(g, 0, sizeof g);
        for (int i = 1; i <= m; i++)
        {
            char str[5];
            cin >> str;
            int a = str[0] - 'A', b = str[2] - 'A';

            if (!type)
            {
                g[a][b] = 1;
                floyd();
                type = check();
                if (type)
                    t = i;
            }
        }
        if (!type)
            cout << "Sorted sequence cannot be determined." << endl;
        else if (type == 2)
            cout << "Inconsistency found after " << t << " relations." << endl;
        else
        {
            memset(st, 0, sizeof st);
            printf("Sorted sequence determined after %d relations: ", t);
            for (int i = 0; i < n; i++)
                printf("%c", get_min());
            cout << "." << endl;
        }
    }
    return 0;
}
#endif
