/*
【题目】22,矩形
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
//HZOJ 51
int main22()
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

	//dp[i][j]i,jʾʾϷ꣺Ͻǣ½ǵϷ
	//f[i][j]ʾiJİɫ
	//
	int n,m;
	cin >> n >> m;
	int dp[1005][1005] = { 0 };
	int f[1005][1005] = { 0 };
	/*int up[1005][1005] = {0}, left[1005][1005] = {0};
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
		{
			scanf("%d", &dp[i][j]);
			if (dp[i][j])
			{
				left[i][j] = 1 + left[i][j - 1];
				up[i][j] = 1 + up[i - 1][j];
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1]- dp[i - 1][j - 1];
				int ans = 0;
				int temp = up[i][j];
				for (int x = 0;x < left[i][j];x++)
				{
					if (temp > up[i][j-x])temp = up[i][j-x];
					ans += temp;
				}
				dp[i][j] += ans;
			}
			else
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1]- dp[i - 1][j - 1];
			dp[i][j] %= 100007;
		}
	}
	cout << dp[n][m];*/
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
		{
			scanf("%d", &f[i][j]);
		}
	}
	for (int i = n-1;i >=1 ;i--)
	{
		for (int j = 1;j <= m;j++)
		{
			if (f[i][j]) f[i][j] += f[i + 1][j];
		}
	}
	int ans = 0;
	for (int i = 1;i <= n;i++)
	{
		for (int j = m;j >= 1;j--)
		{
			int k = j;
			while (k <= m && f[i][k] >= f[i][j])k++;
			dp[i][j] = f[i][j] * (k - j) + dp[i][k];//ɴ˿Կһ޹أԸΪһλ
			//Сڹϵջ
			dp[i][j] %= 100007;
			ans += dp[i][j];
			ans %= 100007;
		}
	}
	cout << ans;

	//Ż


	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}