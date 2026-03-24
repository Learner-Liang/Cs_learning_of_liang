/*
【题目】6 ,程序自动分析
【整体算法思路】
步骤1：读取输入并完成初始化。先把题目给的数字/字符串准确放进变量。
目的：只有输入含义搞清楚，后面 for/while 的边界与数组下标才不会写错。
步骤2：建立数据结构/状态定义（尤其是 DP 的 dp[i][j] 到底表示什么）。
目的：把“题目文字”翻译成“程序状态”；定义不清，转移方程一定写不对。
步骤3：执行核心算法（循环/递归/搜索/转移），把子问题答案逐步合成总答案。
目的：每一轮循环都要回答“我现在在解决哪个子问题，为什么这样更新是正确的”。
步骤4：输出结果并结束程序。输出下标必须和状态定义一一对应。
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
		
		// 步骤3细化（核心循环解释）：for/while 的顺序不是随便写的，它决定“先用哪些已知结果”。
		// 顺序背后的原理：0/1 背包常用倒序防止同一物品被重复选；图最短路按当前最优点扩展才满足贪心前提。
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
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行更新，把“已知子问题”推到“当前问题”。
// 目的：让小问题先解、大问题后解；若是 DP，要先说清状态定义，再写状态转移方程。
// 关键代码说明：max/min/松弛语句对应数学关系；循环顺序和 if 条件共同保证“不会漏解、不会重算、不会越界”。

// 步骤3细化（判断条件解释）：这个 if/while 是“题目约束”的程序化表达，用来过滤非法状态。
// 为什么这么写：若不先判断就更新，常见后果是越界、重复使用元素或把不可能状态算进去。

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