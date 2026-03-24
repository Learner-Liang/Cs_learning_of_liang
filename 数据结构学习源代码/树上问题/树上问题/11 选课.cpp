/*
【题目】11 选课
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
#include <vector>
#include <map>
using namespace std;
vector<int>g[305];
int valk[305] = { 0 };
int countt[305] = { 0 };
void GETDP(int (*dp)[305],int m,int fa,int son);
int main10()
{
	int n, m;
	cin >> n >> m;
	int dp[305][305] = { 0 };
	for (int i = 1,a,b;i <= n;i++)
	{
		scanf("%d%d", &a, &b);
		valk[i] = b;
		g[a].push_back(i);
	}
	m += 1;
	GETDP(dp, m, -1, 0);
	cout << dp[0][m];
	return 0;
}
void GETDP(int (*dp)[305],int m,int fa,int son)
{
	countt[son] = 1;
	//dp[son][0] = 0;
	dp[son][1] = valk[son];
	int n = g[son].size();
	for (int i = 0;i < n;i++)
	{
		GETDP(dp, m, son, g[son][i]);
		countt[son] += countt[g[son][i]];
		for (int j = min(m, countt[son]);j>=2;j--)
		{
			int s = j - 1;
			for (int k = 1;k <= countt[g[son][i]];k++)
			{
				if (k > s)break;
				dp[son][j] = max(dp[son][j], dp[son][j - k] + dp[g[son][i]][k]);
			}
		}
	}
	return;

}