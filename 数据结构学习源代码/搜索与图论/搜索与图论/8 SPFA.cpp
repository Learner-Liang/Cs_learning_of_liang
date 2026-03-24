/*
【题目】8 SPFA
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

int count1[100] = { 0 };
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
				if (count1[e[i]] >= n) {};//ڸ
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
				if (count1[e[i]] >= n) {};//ڸ
			}
		}
	}
	if (dis[n] > 0x3f3f3f3f / 2)return -1;
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
	for (int i = 0, x, y, z;i < m;i++)
	{
		cin >> x >> y >> z;
		add_edge(x, y, z);
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}