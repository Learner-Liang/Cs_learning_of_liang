/*
【题目】12 简单版本
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
#include <queue>
#include <queue>
using namespace std;
#define max 1000000
//ͬʱţͳƵʳִ
int node[max + 5][26] = { 0 };
int val1[max + 4] = { 0 };
int node_cnt = 1, root = 1;
char s[max + 5];
int fail[max + 5] = { 0 };

void insert_ac1(const char* s)
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

	int p = root;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		if (node[p][ind] == 0)node[p][ind] = ++node_cnt;
		p = node[p][ind];
	}
	val1[p]++;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return;
}
void build_ac1()
{
	//headtailģ
	int p = root;
	queue<int>q;
	for (int i = 0;i < 26;i++)
	{
		//if (node[p][i] == 0)node[p][i]=root;
		fail[node[p][i]] = root;
		if (node[p][i] == 0)
		{
			//node[p][i] = root;
			continue;
		}
		q.push(node[p][i]);
	}
	while (!q.empty())
	{
		int temp = q.front();
		q.pop();
		for (int i = 0;i < 26;i++)
		{
			if (node[temp][i] == 0)
			{
				if (fail[temp] == 0)
					node[temp][i] = root;
				else
					node[temp][i] = node[fail[temp]][i];
				continue;
			}
			p = fail[temp];
			if (p == 0)p = root;
			else p = node[p][i];
			fail[node[temp][i]] = p;
			q.push(node[temp][i]);

		}
	}
	return;
}
int main12()
{
	int n;
	cin >> n;
	for (int i = 0;i < n;i++)
	{
		cin >> s;
		insert_ac1(s);
	}
	cin >> s;
	build_ac1();
	int ans = 0;
	int p = root, q;
	for (int i=0;s[i];i++)
	{
		int ind = s[i] - 'a';
		p = node[p][ind];
		q = p;
		while (q>1&&val1[q]!=-1)
		{
			ans += val1[q];
			val1[q] = -1;
			q = fail[q];
		}
	}
	cout << ans;
	return 0;
}