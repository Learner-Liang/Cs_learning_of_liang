/*
【题目】28,魔族密码
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
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <cstring>
using namespace std;
string word[2005];
bool is_valid(int i, int j)
{
	if (word[i].size() >= word[j].size())return false;
	for (int x = 0;word[i][x];x++)
	{
		if (word[i][x] != word[j][x])return false;
	}
	return true;
}
//p1481
int main28()
{
	int dp[2005] = { 0 };
	int n;
	cin >> n;
	int ans = 0;
	for (int i = 0;i < n;i++)
	{
		cin >> word[i];
		dp[i] = 1;
		for (int j = 0;j < i;j++)
		{
			if (is_valid(j, i))
				dp[i] = max(dp[j] + 1, dp[i]);
		}
		ans = max(ans, dp[i]);
	}
	return 0;
}