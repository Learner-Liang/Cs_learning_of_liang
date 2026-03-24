/*
【题目】5 求组合数
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
int dp[1000][1000] = { 0 };
int mod = 10e9 + 7;
//Ʒ
void combination()
{
	for (int i = 0;i < 500;i++)
	{
		for (int j = 0;j <= i;j++)
		{
			if (!j)dp[i][j] = 1;
			else dp[i][j] = dp[i - 1][j] + dp[i - 1][j];
		}
	}
}
int quick_m(int a, int p, int mod)
{
	int ans = 1;
	while (p)
	{
		if (p & 1)
		{
			ans = ans * a % mod;
		}
		a = a * a % mod;
		p >>= 2;
	}
	return ans % mod;
}
//׳Ԫ
//Ԥ
int f[1000] = { 0 }, inf[1000] = { 0 };
void pre_combination()
{
	f[0] = inf[0] = 1;
	for (int i = 1;i < 500;i++)
	{
		f[i] = f[i - 1] * i % mod;
		inf[i] = quick_m(i, mod - 2, mod) % mod;
	}
}

//¬˹
int C(int a, int b, int p)
{
	int pre = 1;
	for (int i = 1;i <= a;i++)
	{
		pre = pre * i % p;
	}
	pre = quick_m(b, p - 2, p) * quick_m(a - b, p - 2, p) % p;
	return pre;
}
int lukas(int a, int b, int p)
{
	if (a < p && b < p)
	{
		return C(a, b, p) % p;
	}
	else return lukas(a % p, b % p, p) * lukas(a / p, b / p, p);
}
int main()
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

	int a, b;
	cin >> a >> b;
	combination();
	cout << dp[a][b];

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}