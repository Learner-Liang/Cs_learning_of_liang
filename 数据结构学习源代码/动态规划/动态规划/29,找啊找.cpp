/*
【题目】29,找啊找
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

//p1509
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <cstring>
using namespace std;
int main29()
{
	int dp[105][105] = { 0 }, Min_time[105][105] = { 0 };
	int rmb[104] = { 0 }, rp[104] = { 0 }, time[104] = { 0 };
	int n, m, r;
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		scanf("%d%d%d", rmb + i, rp + i, time + i);
	}
	cin >> m >> r;
	for (int i = 1;i <= n;i++)
	{
		for (int x = m;m >= rmb[i];x--)
		{
			for (int y = r;y >= rp[i];y--)
			{
				if (dp[x][y] < dp[x - rmb[i]][y - rp[i]] + 1)
				{
					dp[x][y] = dp[x - rmb[i]][y - rp[i]] + 1;
					Min_time[x][y] = Min_time[x - rmb[i]][y - rp[i]] + time[i];
				}
				else if (dp[x][y] == dp[x - rmb[i]][y - rp[i]] + 1)
				{
					Min_time[x][y] = min(Min_time[x][y], Min_time[x - rmb[i]][y - rp[i]] + time[i]);
				}
			}
		}
	}
	cout << Min_time[m][n];
	return 0;
}