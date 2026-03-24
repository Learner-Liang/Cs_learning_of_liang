/*
【题目】25，杂物
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
using namespace std;
//p1113
int main25()
{
	vector<int>len(10005, 0);
	vector<int>dp(10005, 0);
	dp[0]=0;
	int n;
	cin >> n;
	for (int i = 1,a;i <= n;i++)
	{
		scanf("%d", &a);
		scanf("%d", &a);
		len[i] = a;
		scanf("%d", &a);
		dp[i] = min(dp[i], dp[a] + len[i]);
		while (a)
		{
			scanf("%d", &a);
			if(a)dp[i] = max(dp[i], dp[a] + len[i]);
		}
	}
	cout << dp[n];
	return 0;
}