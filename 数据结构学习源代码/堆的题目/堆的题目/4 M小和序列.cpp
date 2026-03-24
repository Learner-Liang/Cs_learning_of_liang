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
	return 0;
}