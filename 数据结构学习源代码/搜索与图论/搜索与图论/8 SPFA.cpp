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

int count1[100] = { 0 };
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


int spfa()
{
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	dis[1] = 0;
	count1[1] = 0;
	queue<int>q;
	q.push(1);
	st[1] = 1;
	while (q.size())
	{
		int t = q.front();
		q.pop();
		st[t] = 0;
		for (int i = h[t];i != -1;i = ne[i])
		{
			if (dis[e[i]] > dis[t] + w[i])
			{
				if (!st[e[i]])
				{
					q.push(e[i]);
					st[e[i]] = 1;
				}
				dis[e[i]] = dis[t] + w[i];
				count1[e[i]] = count1[t] + 1;
				if (count1[e[i]] >= n) {};//存在负环
			}
		}
	}
	if (dis[n] > 0x3f3f3f3f / 2)return -1;
	return dis[n];
}
int spfa1()
{
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	dis[1] = 0;
	count1[1] = 0;
	queue<int>q;
	for (int i = 1;i <= n;i++)
	{
		q.push(i);
		st[i] = 1;
	}
	while (q.size())
	{
		int t = q.front();
		q.pop();
		st[t] = 0;
		for (int i = h[t];i != -1;i = ne[i])
		{
			if (dis[e[i]] > dis[t] + w[i])
			{
				if (!st[e[i]])
				{
					q.push(e[i]);
					st[e[i]] = 1;
				}
				dis[e[i]] = dis[t] + w[i];
				count1[e[i]] = count1[t] + 1;
				if (count1[e[i]] >= n) {};//存在负环
			}
		}
	}
	if (dis[n] > 0x3f3f3f3f / 2)return -1;
	return dis[n];
}
int main()
{
	memset(h, -1, sizeof(h));
	memset(g, 0x3f3f3f3f, sizeof(g));
	cin >> n >> m;
	for (int i = 0, x, y, z;i < m;i++)
	{
		cin >> x >> y >> z;
		add_edge(x, y, z);
	}
	return 0;
}