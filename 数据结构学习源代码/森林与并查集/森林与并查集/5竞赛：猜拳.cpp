//是否已知两个人的输赢关系作为并集，知道的在同一集合中
//带权并查集：x->y的路径上，x每输一次加1（赢一次也行）
//权值cha对3取余,权值是相对根节点而言，因而用权值cah
//0：平局 1：x赢  2：y赢//取决与调换顺序与方法
//等价权值
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
#include <unordered_map>
#include <string>
using namespace std;
int n, m;
int fa[10005] = { 0 }, val[10005] = { 0 };
int find(int x)
{
	if (fa[x] == x)return x;
	int res = fa[x];
	fa[x] = find(fa[x]);
	val[x] = (val[res] + val[x] + 3) % 3;
	return fa[x];
}
void merge(int a, int b, int t)
{
	int aa = find(a), bb = find(b);
	if (aa == bb)return;
	fa[aa] = bb;
	val[aa] = (t + val[b] - val[a] + 3) % 3;
	return;
}
int main()
{
	cin >> n >> m;
	for (int i = 0;i <= n;i++)fa[i] = i;
	for (int i = 0, a, b, c;i < m;i++)
	{
		cin >> a >> b >> c;
		if (a == 1)merge(b, c, 1);
		else
		{
			int aa = find(b), bb = find(c);
			if (aa != bb)printf("Unknown\n");
			else
			{
				int v = (val[b] - val[c] + 3) % 3;
				if (v == 1)printf("Win\n");
				else if (v == 2)printf("Loss\n");
				else printf("Tie\n");
			}
		}
	}
	return 0;
}