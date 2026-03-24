/*
【题目】8 跨越  树的直径
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
using namespace std;
/*һ n ûбȨֱǶ٣ϵ·Ƕ١*/
//ڵֵȷ
//ͬʱӽڵ븸ڵתƹϵ֮⣬ҪǿԽڵתƹϵ


//dp[x]=max(dp[xson]+1)
//\ans=max(ans,dp[x1]+dp[x2+2])
//dp[x]xΪ˵㣬µ·
int count1 = 0;
struct EDGE
{
	int son_val, son;
};
int max_ans = 0;
void _add_(int* head, EDGE* edge, int a, int b)
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

	edge[++(count1)] = { b,head[a] };
	head[a] = count1;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return;
}
void get_jump_dp(int* head, EDGE* edge, int* dp, int f,int s)
{
	int x1 = -1, x2 = -1;//ûнڵ㣬ͻᵼΪ2Ĭֵ2ֵͨΪ-1ԽĬֵΪ0
	for (int p = head[s];p;p = edge[p].son)
	{
		int to = edge[p].son_val;
		if (to == f)continue;
		get_jump_dp(head, edge ,dp, s, to);
		dp[s] = max(dp[s], dp[to]+1);
		if (dp[to] > x1)x2 = x1, x1 = dp[to];
		else if (dp[to] > x2)x2 = dp[to];
	}
	max_ans = max(max_ans,x1+x2+ 2);
	return;
}
int main8()
{
	int n;
	cin >> n;
	int head[100] = { 0 };
	EDGE edge[100] = { 0 };
	int dp[100] = { 0 };
	for (int i = 1,a,b;i < n;i++)
	{
		cin >> a >> b;
		_add_(head, edge, a, b);
		_add_(head, edge, b, a);

	}
	//for (int i = 1;i <= n;i++)cout << head[i] << endl;
	get_jump_dp(head, edge,dp,0,1);
	cout << max_ans;
	return 0;
}