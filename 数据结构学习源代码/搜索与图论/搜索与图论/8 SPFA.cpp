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

// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

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
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
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
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行状态更新，逐步逼近最优解/可行解。
// 目的：把局部决策累积为全局答案；若是 DP，本质是“已知子问题 -> 当前问题”的转移。
// 关键代码说明：max/min/松弛/合并等更新语句是核心；它们对应题目中的数学关系或最优性原理。

	memset(h, -1, sizeof(h));
	memset(g, 0x3f3f3f3f, sizeof(g));
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	cin >> n >> m;
	for (int i = 0, x, y, z;i < m;i++)
	{
		cin >> x >> y >> z;
		add_edge(x, y, z);
	}
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。

// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return 0;
}