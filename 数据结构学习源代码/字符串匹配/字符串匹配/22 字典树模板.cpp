/*
【题目】22 字典树模板
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

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;
int node4[3000005][62] = {
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
int val4[3000005] = { 0 };
char s[1000000] = { 0 };
int root4 = 1, cnt4 = 1;
int code(char c)
{
	if (c <= 'z' && c >= 'a')

// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return c - 'a';
	else if ((c <= 'Z') && c >= 'A')return c - 'A' + 26;
	else return c - '0' + 52;
}
void insert_tree(const char* s)
{
	int p = root4;
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
	for (int i = 0;s[i];i++)
	{
		val4[p]++;
		int ind = code(s[i]);
		if (node4[p][ind] == 0)node4[p][ind] = ++cnt4;
		p = node4[p][ind];
	}
	val4[p]++;
	return;
}
int find_time(const char* s)
{
	int p = root4;
	for (int i = 0;s[i];i++)
	{
		int ind = code(s[i]);
		if (node4[p][ind] == 0)return 0;
		p = node4[p][ind];
	}
	return val4[p];
}
void init_tree()
{
	for (int i = 0;i <= cnt4;i++)
	{
		val4[i] = 0;
		for (int j = 0;i < 62;j++)node4[i][j] = 0;
	}
	cnt4 = 1;
	root4 = 1;
	return;
}
void solve()
{
	init_tree();
	int n, q;
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	cin >> n >> q;
	for (int i = 0;i < n;i++)
	{
		cin >> s;
		insert_tree(s);
	}
	for (int i = 0;i < q;i++)
	{
		cin >> s;
		
		// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
		cout << find_time(s) << endl;
	}
}
int main22()
{
	int N;
	cin >> N;
	while (N--)solve();
	return 0;
}