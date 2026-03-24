/*
【题目】5 无根树转有根树
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

//没有明确的根节点，假设一个根节点
// notepad
//解题思路：有的题目看成树会很好接解决
#define _CRT_SECURE_NO_WARNINGS
/*在 W 星球上有 n 个国家。为了各自国家的经济发展，他们决定在各个国家之间建设双向道路使得国家之间连通。但是每个国家的国王都很吝啬，
他们只愿意修建恰好 n−1 条双向道路。
每条道路的修建都要付出一定的费用，这个费用等于道路长度乘以道路两端 的国家个数之差的绝对值。例如，在下图中，
虚线所示道路两端分别有 2 个、4 个国家，如果该道路长度为 1，则费用为 1×∣2−4∣=2。图中圆圈里的数字表示国家的编号。*/
#include <iostream>
using namespace std;
struct edge
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

	int first = 0, second = 0;
	int price=0;
};
int cnt_ = 0;
int n;
int nums[100] = { 0 };
void add__(edge* edge, int* head, int a, int b,int price)
{
	edge[++cnt_] = { b,head[a],price };
	head[a] = cnt_;
	

// 步骤4（代码实现）：输出结果并返回。
// 目的：给出最终答案并结束程序执行。
// 实现：调用输出语句打印结果，并通过 return 结束流程。
return;
}
int ans899 = 0;
void dfs1(int* head, edge* edge, int f, int s)
{
	nums[s] = 1;
	int p = head[s];
	while (p)
	{
		int to = edge[p].first;
		if (to != f)
		{
			dfs1(head, edge, s, to);
			nums[s] += nums[to];
			ans899 += edge[p].price * abs(n - nums[to] * 2);
		}
		p = edge[p].second;
	}
}
int getprice(edge* edge, int* head, int root)//错误，必须要父节点防止出现无限递归问题
{
	int sum = 0;
	int p = head[root];
	while (p)
	{
		int to = edge[p].first;
		if (to != root)
		{
			cout << sum;
			sum += (edge[p].price) * abs(n - nums[to]*2);
		    sum +=getprice(edge, head, to);
		}
		p = edge[p].second;
	}
	return sum;
}
int main5()
{
	cin >> n;
	int head[100] = { 0 };
	edge Edge[200] = { 0 };
	for (int i = 1,a,b,c;i < n;i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		add__(Edge, head, a, b, c);
		add__(Edge, head, b, a, c);
	}
	dfs1(head,Edge,0, 1);
	//getprice(Edge, head, 1);
	cout << ans899;
	//cout << getprice(Edge,head,1);
	return 0;
}