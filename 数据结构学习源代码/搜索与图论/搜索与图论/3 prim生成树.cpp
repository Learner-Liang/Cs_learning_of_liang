#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, g[100][100], d[100];
bool st[100] = { 0 };

int prim()
{
	memset(d, 0x3f, sizeof(d));
	int res = 0;
	for (int i = 1;i <= n;i++)
	{
		int t = -1;
		for (int j = 1;j <= n;j++)
		{
			if (st[j] == 0 && (t == -1 || d[j] < d[t]))
			{
				t = j;
			}
		}
		if (i > 1 && d[t] == 0x3f3f3f3f)return 0x3f3f3f3f;
		if (i > 1)res += d[t];
		st[t] = 1;
		for (int j = 1;j <= n;j++)
		{
			if (st[j] == 0)d[j] = min(d[j], g[t][j]);//为集合距离，应该是g[t][j]
		}
	}
	return res;
}
int main()
{
	memset(g, 0x3f, sizeof(g));
	cin >> n >> m;
	for (int i = 0, x, y, z;i < m;i++)
	{
		cin >> x >> y >> z;
		g[x][y] = g[y][x] = min(z, g[x][y]);
	}
	return 0;
}