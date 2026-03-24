/*
【题目】4 M小和序列
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
#include <set>
#include <algorithm>
#include <string>
#include <queue>
#include <map>
#include <set>
using namespace std;
/*给出一个 n∗m
n∗m
 的矩阵，每行取一个元素，组成一个包含 n
 个元素的序列，一共有 mn
 种序列，求出序列和最小的前 m
 个序列的序列和。*/
int n, m;
int a[2005] = { 0 };
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

	cin >> n >> m;
	multiset<int>s[2];
	int ind1, ind2;
	int g;
	for (int i = 0;i < m;i++)
	{
		scanf_s("%d", a + i);
		s[0].insert(-a[i]);
	}
	int c;
	for (int i = 1;i < n;i++)
	{
		ind1 = i % 2;
		ind2 = 1 - ind1;
		s[ind1].clear();
		for (int z = 0;z < m;z++)
		{
			scanf_s("%d", &c);
			for (auto x : s[ind2])
			{
				g = x - c;
				if (s[ind1].size() <= m || g > *s[ind1].begin())
					s[ind1].insert(g);
				if (s[ind1].size() > m)s[ind1].erase(s[ind1].begin());
			}
		}
	}
	int count = 0;
	for (auto x : s[ind1])
	{
		a[m - count] = -x;
		count++;
	}
	for (int i = 1;i <= m;i++)
	{
		cout << a[i];
		if (i < m)cout << " ";
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}