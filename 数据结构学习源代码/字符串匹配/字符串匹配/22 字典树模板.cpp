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
int node4[3000005][62] = { 0 };
int val4[3000005] = { 0 };
char s[1000000] = { 0 };
int root4 = 1, cnt4 = 1;
int code(char c)
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

	if (c <= 'z' && c >= 'a')return c - 'a';
	else if ((c <= 'Z') && c >= 'A')return c - 'A' + 26;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	else return c - '0' + 52;
}
void insert_tree(const char* s)
{
	int p = root4;
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
	cin >> n >> q;
	for (int i = 0;i < n;i++)
	{
		cin >> s;
		insert_tree(s);
	}
	for (int i = 0;i < q;i++)
	{
		cin >> s;
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