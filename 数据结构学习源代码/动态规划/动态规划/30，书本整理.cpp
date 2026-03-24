/*
【题目】30，书本整理
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
struct book
{
	int h, w;
};
int main30()
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

	int n, k;
	cin >> n >> k;
	//dp[i][k]=min(dp[j][k-1]+w[i]-w[j])ǰiѡkiѡ
	struct book books[105];
	int K = n - k;
	vector<vector<int>>dp(105,vector<int>(105,0x3f3f3f));
	for (int i = 1;i <= n;i++)
	{
		cin >> books[i].h >> books[i].w;
	}
	sort(books+1, books +1+ n, [&](const book& a, const book& b)->bool
		{
			return a.h < b.h;
		});
	int ans = 0x3f3f3f;
	for (int i = 1;i <= n;i++)
	{
		dp[i][0] = dp[i][1] = 0;
		for (int j = 2;j <= i;j++)
		{
			for (int x = j-1;x < i;x++)
				dp[i][j] = min(dp[i][j], dp[x][j - 1] + abs(books[i].w - books[x].w));
		}
		ans = min(ans, dp[i][K]);
	}
	cout << ans;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}