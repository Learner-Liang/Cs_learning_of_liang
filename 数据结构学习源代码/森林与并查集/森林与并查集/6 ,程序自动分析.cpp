/*
【题目】6 ,程序自动分析
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
#include <vector>
#include <unordered_map>
using namespace std;
class unionset {
public:
	unionset(int n) :p(n + 1)
	{
		
		// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
		// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
		for (int i = 0;i <= n;i++)
			p[i] = i;
	}
	int find(int a)
	{
		if (p[a] == a)return a;
		return p[a] = find(p[a]);
	}
	void merge(int a, int b)
	{
		int aa = find(a), bb = find(b);
		if (aa == bb)return;
		p[a] = bb;
		return;
	}
	vector<int>p;
};
typedef struct Node
{
	int i, j, e;
}Node;
//int find_same(unionset& s, int n);
int solve()
{
	int n;
	scanf("%d", &n);
	vector<Node>N(n);
	unordered_map<int,int>m;
	int cnt = 0;
	for (int i = 0;i < n;i++)
	{
		scanf("%d%d%d", &N[i].i, &N[i].j, &N[i].e);
		if (m.find(N[i].i) == m.end()) m[N[i].i] = cnt++;
		if (m.find(N[i].j) == m.end()) m[N[i].j] = cnt++;
	}
	unionset u(2 * n);
	for (int i = 0;i < n;i++)
	{
		if (N[i].e == 0)continue;
		u.merge(m[N[i].i], m[N[i].j]);
	}
	for (int i = 0;i < n;i++)
	{
		if (N[i].e == 1)continue;
		if (u.find(m[N[i].i]) == u.find(m[N[i].j]))
			return 0;
	}
	return 1;
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

// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

	int n;
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	cin >> n;
	while (n--)
	{
		
		// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
		if (solve())printf("YES\n");
		else printf("NO\n");
	}
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return 0;
}
//̫޷
/*int find_same(unionset& s, int n)
{
	if (n == 0)return 1;
	int i, j, e;
	scanf("%d%d%d", &i, &j, &e);
	if (e == 1)
	{
		s.merge(i, j);
		return find_same(s, n - 1);
	}
	else
	{
		if (find_same(s, n - 1))
		{
			if (s.find(i) != s.find(j))
				return 1;
		}
		return 0;
	}
}*/



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
#include <unordered_set>
using namespace std;
typedef pair<int, int> P;
int t, n;
int find(vector<int>& fa, int x)
{
	if (fa[x] == x)return x;
	fa[x] = find(fa, fa[x]);
	return fa[x];
}
void merge(vector<int>& fa, int a, int b)
{
	int aa = find(fa, a), bb = find(fa, b);
	if (aa == bb)return;
	fa[aa] = bb;
	return;
}
int main()
{
	cin >> t;
	for (int i = 0;i < t;i++)
	{
		cin >> n;
		unordered_map<int, int>m;
		set<P>s;
		int k = n * 2 + 2, cnt = 0;
		vector<int>fa(k);
		for (int j = 0;j < k;j++)fa[j] = j;
		for (int j = 0, a, b, c;j < n;j++)
		{
			cin >> a >> b >> c;
			if (m.find(b) == m.end())m[b] = cnt++;
			if (m.find(a) == m.end())m[a] = cnt++;
			if (c == 1)merge(fa, m[a], m[b]);
			else s.insert(P{ m[a],m[b] });
		}
		int flag = 1;
		for (auto xx : s)
		{
			int x = xx.first, y = xx.second;
			int aa = find(fa, x), bb = find(fa, y);
			if (aa != bb)continue;
			else
			{
				flag = 0;
				break;
			}
		}
		if (flag)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}