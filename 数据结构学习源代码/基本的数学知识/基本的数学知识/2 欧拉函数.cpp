/*
【题目】2 欧拉函数
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
int num_oula(int n)//
{
	int ans = n;
	for (int i = 2;i <= n / i;i++)
	{
		if (n % i == 0)
		{
			ans = ans * (i - 1) / i;
			while (n % i == 0)n /= i;
		}
	}
	if (n > 1)ans *= (n - 1) / n;
	return ans;
}
int primes[10000] = { 0 }, cnt = 0;
int phi[10000] = { 0 };
bool st[10000] = { 0 };
int get_eulers(int n)//ɸ1nŷ֮
{
	int ans = 0;
	phi[1] = 1;
	for (int i = 2;i <= n;i++)
	{
		if (!st[i])
		{
			primes[cnt++] = i;
			phi[i] = i - 1;
		}
		for (int j = 0;primes[j] <= n / i;j++)
		{
			st[primes[j] * i] = 1;
			if (i % primes[j] == 0)
			{
				phi[primes[j] * i] = primes[j] * phi[i];
				break;
			}
			else
			{
				phi[i * primes[j]] = phi[i] * phi[primes[j]];
			}
		}
	}
	for (int i = 1;i <= n;i++)ans += phi[i];
	return ans;
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

	int n;
	cin >> n;
	cout << num_oula(n) << endl;
	cout << get_eulers(n) << endl;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}