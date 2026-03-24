/*
【题目】35，仓库建设
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
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
int main()
{
	int x[105] = { 0 }, p[105] = { 0 }, c[105] = { 0 };
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		scanf("%d%d%d", x + i, p + i, c + i);
	}
	int cost[105][105] = { 0 };
	for (int i = 1;i <= n;i++)
	{
		for (int j = i-1;j>=1;j--)
		{
			cost[j][i] = cost[j + 1][i] + (x[i] - x[j]) * p[j];
		}
	}
	for (int i = 1;i <= n;i++)
	{

	}
	return 0;
}