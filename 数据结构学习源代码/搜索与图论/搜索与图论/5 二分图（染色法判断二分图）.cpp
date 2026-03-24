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
int h[100], e[100], ne[100];
int color[100] = { 0 }, cnt = 0;
int n, m;
void add_edge(int a, int b)
{
	e[cnt] = b;
	ne[cnt] = h[a];
	h[a] = cnt;
	cnt++;
	return;
}
int dfs(int a, int flag)
{
	if (color[a] == -1)color[a] = flag;
	else if (color[a] == 1 - flag)return 0;//表示不能形成二分图
	else return 1;
	for (int i = h[a];i != -1;i = ne[i])
	{
		if (dfs(e[i], 1 - flag) == 0)return 0;
	}
	return 1;
}
int main()
{
	cin >> n >> m;
	for (int i = 1;i <= n;i++)h[i] = -1;
	for (int i = 1;i <= n;i++)color[i] = -1;
	for (int i = 0, x, y;i < m;i++)
	{
		cin >> x >> y;
		add_edge(x, y);
		add_edge(y, x);
	}
	return 0;
}