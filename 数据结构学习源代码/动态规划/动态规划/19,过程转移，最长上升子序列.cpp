/*
【题目】19,过程转移，最长上升子序列
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
using namespace std;
int binary_search(vector<int>& len, int n, int x)
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

	int head = 0,tail = n, mid;
	while (head < tail)
	{
		mid = (head + tail + 1) >> 1;
		if (len[mid] < x)head = mid;
		else
			tail = mid - 1;
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return head;
}
int main19()
{
	//dp[i]ʾiλΪβ
	//len[j]ʾΪjһλСֵ,lenǵģʹöַ
	int n;
	cin >> n;
	vector<int>dp(1000005, 1), len(1000005, 0x3f3f3f3f), a(1000005);
	for (int i = 1, k;i <= n;i++)

	{
		scanf("%d", &k);
		a[i] = k;
	}
	/*int ans = 0;
	len[1] = a[1];
	for (int i = 1;i <= n;i++)
	{
		for (int j = i - 1;j > 0;j--)
		{
			if (a[i] > len[j])
			{
				dp[i] = j + 1;
				ans = max(ans, j + 1);
				len[dp[i]] = min(a[i], len[dp[i]]);
				break;
			}
		}
		len[1] = min(len[1], a[i]);
	}
	cout << ans;*/
	len[0] = -1;
	int ans = 0;
	for (int i = 1;i <= n;i++)
	{
		dp[i] = binary_search(len,ans,a[i]) + 1;
		len[dp[i]] = a[i];
		if (dp[i] > ans)ans = dp[i];
	}
	cout << ans;
	return 0;
}