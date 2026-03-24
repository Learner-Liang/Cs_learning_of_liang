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
int h[100], e[1000], ne[1000], cnt = 0, d[1000] = { 0 };
bool st[1000] = { 0 };
//¼Ó±ß
void add_edge(int a, int b)
{
	e[cnt] = b;
	ne[cnt] = h[a];
	h[a] = cnt++;
	return;
}
int ans = 0x3f3f3f3f, n;
void bfs(int head)
{
	queue<int>q;
	q.push(head);
	while (q.size())
	{
		int temp = q.front();
		q.pop();
		for (int i = h[temp];i != -1;i = ne[i])
		{
			if (st[e[i]] != 1)
			{
				q.push(e[i]);
				d[e[i]] = d[temp] + 1;
			}
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	cin >> n;
	for (int i = 0, a, b;i < n;i++)
	{
		cin >> a >> b;
		if (a != b)add_edge(a, b);
	}
	return 0;
}