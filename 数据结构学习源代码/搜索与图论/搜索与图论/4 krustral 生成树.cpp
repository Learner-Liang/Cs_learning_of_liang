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
typedef struct Edge
{
	int a, b, w;
}Edge;
Edge edge[100] = { 0 };
int n, m, cnt = 0;
int p[100];
int find(int a)
{
	if (p[a] != a) p[a] = find(p[a]);
	return p[a];
}
void add(int a, int b) {
	int aa = find(a), bb = find(b);
	if (aa == bb)return;
	p[aa] = bb;
	return;
}
int ans = 0;
int main()
{
	cin >> n >> m;
	for (int i = 0, x, y, z;i < m;i++)
	{
		cin >> x >> y >> z;
		edge[i] = { x,y,z };
	}
	for (int i = 1;i <= n;i++)p[i] = i;
	sort(edge, edge + m, [&](Edge& a, Edge& b)->bool {return a.w < b.w;});
	for (int i = 0, a, b;i < m;i++)
	{
		a = edge[i].a, b = edge[i].b;
		if (find(a) != find(b))
		{
			add(a, b);
			ans += edge[i].w;
			cnt++;
		}
	}
	if (cnt < n - 1)printf("无法生成树");
	else printf("%d", ans);

	return 0;
}