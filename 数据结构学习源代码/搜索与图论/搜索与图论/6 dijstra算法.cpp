/*
【题目】6 dijstra算法
【整体算法思路】
步骤1：读取输入并完成初始化。
目的：将题目数据转换为可计算的状态。
步骤2：建立本题需要的数据结构/状态定义。
目的：为后续核心算法提供正确的信息组织方式。
步骤3：执行核心算法流程（见下方关键函数或循环）。
目的：按题意逐步求解并得到最终答案。
步骤4：输出结果并结束程序。
目的：返回题目要求的结果，完成一次完整求解。
*/

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

int h[100], e[1000], ne[1000], cnt = 0, w[1000] = { 0 };//ڽӾ

bool st[1000] = { 0 };

int dis[100];

int g[100][100] = { 0 };//ڽӱ

typedef pair<int, int> P;//һʾ룬ڶʾ
//ӱ
void add_edge(int a, int b, int c)
{
	e[cnt] = b;
	ne[cnt] = h[a];
	w[cnt] = c;
	h[a] = cnt++;
	return;
}


//ذ
int dijkstra_1()//ڽӾ
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
//Ż
int dijkstra_2()//ڽӱ
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
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	memset(h, -1, sizeof(h));
	memset(g, 0x3f3f3f3f, sizeof(g));
	cin >> n >> m;
	for (int i = 0, x, y;i < m;i++)
	{
		cin >> x >> y;
		cin >> g[x][y];
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}