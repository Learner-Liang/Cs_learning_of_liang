/*
【题目】6单词接龙
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

//·չʴص֣d[x][y]
//ĳ:L+len[y]-d[x][y]
//жϵʹô:vis飺ʱ򣬻Ҫ-1
#include <iostream>
#include <string>
using namespace std;
string s[25];
int d[25][25] = { 0 };
int vis1[25] = { 0 };
int f(string s1, string s2)
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

	int k = s1.size();
	int k1 = s2.size();
	for (int i = k - 1;i >= 1;i--)//ʲȫغ+
	{
		int I = k - i;
			for (int j = 0;j < I;j++)
			{
				if (s1[i + j] != s2[j])break;
				if (j == I - 1) return I;
			}
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
int ans1 = 0;
void dfs5(int now, int sum,int n)
{
	if (sum > ans1)ans1 = sum;
	for (int i = 0;i < n;i++)
	{
		if (d[now][i]==0 || vis1[i] == 2)continue;
		vis1[i]++;
		dfs5(i,sum+ s[i].size() - d[now][i],n);
		vis1[i]--;
	}
}
int main6()
{
	int n;
	cin >> n;
	for (int i = 0;i < n;i++)
	{
		cin >> s[i];
	}
	int ch;
	cin >> ch;
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;i < n;i++)
		{
			d[i][j] = f(s[i], s[j]);
		}
	}
	for (int i = 0;i < n;i++)
	{
		if (s[i][0] != ch) continue;
		vis1[i]++;
		dfs5(i, s[i].size(),n);
		vis1[i]--;
	}
	cout << ans1 << endl;
	return 0;
}