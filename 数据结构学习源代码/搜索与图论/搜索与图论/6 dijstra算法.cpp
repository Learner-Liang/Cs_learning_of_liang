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
int n, m;

int h[100], e[1000], ne[1000], cnt = 0, w[1000] = { 0 };//邻接矩阵

bool st[1000] = { 0 };

int dis[100];

int g[100][100] = { 0 };//邻接表

typedef pair<int, int> P;//第一个表示距离，第二个表示编号
//加边
void add_edge(int a, int b, int c)
{
	e[cnt] = b;
	ne[cnt] = h[a];
	w[cnt] = c;
	h[a] = cnt++;
	return;
}


//朴素版
int dijkstra_1()//用邻接矩阵
{
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	dis[1] = 0;
	for (int i = 0;i < n;i++)
	{
		int t = -1;
		for (int j = 1;j <= n;j++)
		{
			if (st[j] == 0 && (t == -1 || dis[t] > dis[j]))t = j;
		}
		if (t == n)break;
		st[t] = 1;
		for (int j = 1;j <= n;j++)
			dis[j] = min(dis[j], dis[t] + g[t][j]);
	}
	return dis[n];
}
//堆优化
int dijkstra_2()//用邻接表
{
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	dis[1] = 0;
	set<P>s;
	s.insert({ 0,1 });
	while (s.size())
	{
		P temp = *s.begin();
		s.erase(s.begin());
		int ver = temp.second, distance = temp.first;
		if (st[ver])continue;
		for (int i = h[distance];i != -1;i = ne[i])
		{
			int j = e[i];
			if (dis[j] > distance + w[i])
			{
				dis[j] = distance + w[i];
				s.insert({ dis[j],j });
			}
		}
		st[ver] = true;
	}
	return dis[n];
}
int main()
{
	memset(h, -1, sizeof(h));
	memset(g, 0x3f3f3f3f, sizeof(g));
	cin >> n >> m;
	for (int i = 0, x, y;i < m;i++)
	{
		cin >> x >> y;
		cin >> g[x][y];
	}
	return 0;
}