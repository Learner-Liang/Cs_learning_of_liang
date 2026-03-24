/*
【题目】5吃奶酪
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

//ȫ
//֦
//״̬ѹλȨֵ
//״̬ѹ
#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;
typedef struct Node
{
	double x, y;
}Node;
Node p[20];
int ind[70000] = { 0 };//ģϣ
double dp[70000][20] = {0};//dp[x][y],xʾλԼλ֮ǰĵ꣨ÿ궼һӦĶλ֣yʾǰ±
double ans = 1e9;//70000ԭ216η70000
double dis[20][20] = { 0 };
#define s(n)  ((n)*(n))
void dfs4(int t, int now, double s)
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

	if (t == 0)
	{
		ans = min(ans, s);

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
		return;
	}
	for (int k = t;k;k -= (k & (-k)))
	{
		int j = ind[k & (-k)], temp = t - (1 << j);
		if (dp[temp][j] != 0 && dp[temp][j] <= s + dis[now][j]) continue;
		if (s + dis[now][j] >= ans)continue;
		dfs4(temp, j, dis[now][j] + s);
	}
}
int main5()
{
	int n;
	cin >> n;
	p[0].x = p[0].y = 0;
	for (int i = 1;i <= n;i++)
	{
		cin >> p[i].x >> p[i].y;
	}
	for (int i = 0, k = 1;i <= n;k *= 2,i++)ind[k] = i;
	for (int i = 0;i <= n;i++)
	{
		for (int j = i+1;j <= n;j++)
		{
			dis[j][i]=dis[i][j] = sqrt(s(p[i].x - p[j].x) + s(p[i].y - p[j].y));
		}
	}
	dfs4((1 << (n + 1)) - 2,0 , 0);
	printf("%.2llf", ans);
	return 0;
}