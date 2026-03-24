/*
【题目】13 复杂版本
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
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
char s[20][75] = {
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行状态更新，逐步逼近最优解/可行解。
// 目的：把局部决策累积为全局答案；若是 DP，本质是“已知子问题 -> 当前问题”的转移。
// 关键代码说明：max/min/松弛/合并等更新语句是核心；它们对应题目中的数学关系或最优性原理。
 0 };
struct Node {
	vector<int>ind;
	int fail;
	int next[26] = { 0 };
}AC[800];
int cnt_ac[800] = { 0 }, node_cnt1 = 1, root_ = 1;
char S[7000] = { 0 };
int getNewNode()
{
	node_cnt1++;
	AC[node_cnt1].ind.clear();
	AC[node_cnt1].fail = 0;
	memset(AC[node_cnt1].next, 0,sizeof(int)* 26);
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return node_cnt1;
}
void init()
{
	node_cnt1 = 0, root_ = getNewNode();
	root_ = getNewNode();
	memset(cnt_ac, 0, sizeof(char)*800);
}
void insert2(const char* s , int i)
{
	int p = root_;
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		if (AC[p].next[ind] == 0)AC[p].next[ind] = getNewNode();
		p = AC[p].next[ind];
	}
	AC[p].ind.push_back(i);
	return;
}
void build_ac2()
{
	queue<int>que;
	que.push(root_);
	int p;
	while (!que.empty())
	{
		p = que.front();
		int q;
		que.pop();
		if (AC[p].fail)
		{
			int I = AC[AC[p].fail].ind.size();
			for (int i = 0;i < I;i++) {
				AC[p].ind.push_back(AC[AC[p].fail].ind[i]);
			}
		}
		for (int i = 0;i < 26;i++)
		{
			if (AC[p].next[i] == 0)
			{
				if (AC[p].fail == 0)
					AC[p].next[i] = root_;
				else AC[p].next[i] = AC[AC[p].fail].next[i];
				continue;
			}
			q = AC[p].fail;
			if (q == 0)q = root_;
			else q = AC[q].next[i];
			AC[AC[p].next[i]].fail = q;
			que.push(AC[p].next[i]);
		}
	}
}
void find_long()
{
	int p = root_;
	for (int i = 0;S[i];i++)
	{
		int ind = S[i] - 'a';
		p = AC[p].next[ind];
		int I = AC[p].ind.size();
		for (int i = 0;i < I;i++)
		{
			// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
			// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

			cnt_ac[AC[p].ind[i]] += 1;
		}
	}
}
int main13()
{
	int n = 0;
	scanf("%d", &n);
	while (n)
	{
		init();
		for (int i = 0;i < n;i++)
		{
			
			// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
			// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
			cin >> s[i];
			insert2(s[i], i);
		}
		build_ac2();
		cin >> S;
		find_long();
		int ans = 0;
		for (int i = 0;i < n;i++)
		{
			if (cnt_ac[i] > ans)ans = cnt_ac[i];
		}
		
		// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
		cout << ans << endl;;
		for (int i = 0;i < n;i++)
		{
			if (cnt_ac[i] == ans)cout << s[i] << endl;
		}
		scanf("%d", &n);
	}
	return 0;
}