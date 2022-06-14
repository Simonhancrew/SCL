#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/06/12

using namespace std;

/*
	要冲突影响最小，可以考虑二分答案。等价于将大于mid的放在组间，小于mid的关系放在组内
	看看能否形成一个二分图。考虑染色法，2分log(C),每次判断二分图O(n + m),n是点数，m是边数
	总时间O((n + m) * logc)
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
	ios_base::sync_with_stdio(false); \
	cin.tie(nullptr);                 \
	cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 2e4 + 10, M = 2e5 + 10;

int h[N], e[M], ne[M], w[M], idx;
int n, m;
int color[N]; // 0表示未染色，1表示染白色，2表示染黑色，相邻不能染同色

void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool dfs(int u, int c, int mid)
{
	color[u] = c;
	for (int i = h[u]; i != -1; i = ne[i])
	{
		int j = e[i];
		if (w[i] <= mid)
			continue;
		if (color[j])
		{
			if (color[j] == c)
				return false;
		}
		else if (!dfs(j, 3 - c, mid))
			return false;
	}
	return true;
}

bool check(int mid)
{
	memset(color, 0, sizeof color);
	for (int i = 1; i <= n; i++)
	{
		if (!color[i])
		{
			if (!dfs(i, 1, mid))
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	fast_cin();
	cin >> n >> m;
	memset(h, -1, sizeof h);
	while (m--)
	{
		int a, b, c;
		cin >> a >> b >> c;
		add(a, b, c), add(b, a, c);
	}
	int l = 0, r = 1e9;
	while (l < r)
	{
		int mid = l + r >> 1;
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	cout << l << endl;
	return 0;
}