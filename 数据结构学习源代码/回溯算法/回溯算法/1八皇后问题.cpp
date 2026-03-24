/*
【题目】1八皇后问题
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

// p1219 ˻ʺ
#include <iostream>
#include <unordered_map>
using namespace std;
#define Max(n) ((1<<(n+1))-2)
unordered_map<int, int> ind;
int total = 3;
int arr[100] = { 0 };
void printf_( int n)
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

	if (total)
	{
		total--;
		for (int i = 1;i <= n;i++)
			printf("%d  ", arr[i]);
		printf("\n");
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
}
int dfs(int k, int t1, int t2, int t3,int n)
{
	if (k > n)
	{
		printf_(n);
		return 1;
	}
	int ans = 0;
	for (int i = t1;i;i -= (i & (-i)))
	{
		int j = ind[i & (-i)];
		int a1 = (1 << (k + j - 1)), a2 = (1 << (k - j + n));
		if ((t2 & a1) && (t3 & a2))
		{
			arr[k] = j;
			ans += dfs(k + 1, t1 ^ (1 << j), t2 ^ a1, t3 ^a2, n);
		}

	}
	return ans;
}
int main1()
{
	//¼Щֱʹã,˴ÿʺһ
	//Ż״̬ʾ״̬ѹԭıΪ
	//ö٣-t&tԱʾһ֣ò봢棩
	//ڶλt-=(-t&t),湫ʽ
	//бֻܷһ    бߣi+j-1õľб     бi-j+n
	//öƱʾбǷʹ
	int n;
	cin >> n;
	//ùϣλȨλת
	int m = 2 * n;
	for (int i = 0;i < m;i++) ind[1 << i] = i;
	int ans = 0;
	ans = dfs(1, Max(n), Max(m - 1), Max(m - 1),n);
	printf("%d\n", ans);
	return 0;
}