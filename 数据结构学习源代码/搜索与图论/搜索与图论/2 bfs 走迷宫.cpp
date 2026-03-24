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
int m, n;
typedef pair<int, int> P;
int g[100][100], d[100][100] = { 0 };
int dx[4] = { -1,0,1,0 }, dy[4] = { 0,-1,0,1 };
P pre[100][100];
int bfs_1()
{
	queue<P>q;
	q.push(P(0, 0));
	d[0][0] = 1;
	while (q.size())
	{
		P temp = q.front();
		q.pop();
		for (int i = 0;i < 4;i++)
		{
			int x = temp.first + dx[i];
			int y = temp.second + dy[i];
			if (x >= 0 && x < n && y >= 0 && y < m && d[x][y] == 0 && g[x][y] == 0)
			{
				q.push(P(x, y));
				d[x][y] += 1;
				//¼ÇÂ¼Â·¾¶
				pre[x][y] = temp;
			}
		}
	}
	return d[m - 1][n - 1] - 1;
}
int main()
{
	cin >> m >> n;
	for (int x = 0;x < m;x++)
	{
		for (int y = 0;y < n;y++)
		{
			cin >> g[x][y];
		}
	}
	return 0;
}