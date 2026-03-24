/*
【题目】4 高斯消元
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
int n;

int gause(double**& martrix)
{
	int index, r = 0;
	for (int i = 0;i < n;i++)//ö
	{
		index = i;
		for (int j = i;j < n;j++)
		{
			if (abs(martrix[j][i] > martrix[index][i]))index = j;
		}

		if (abs(martrix[index][i]) < 1e-6)continue;



		double* temp = martrix[i];
		martrix[i] = martrix[index];
		martrix[index] = temp;


		for (int j = i + 1;j <= n;j++)martrix[r][j] /= martrix[r][i];
		martrix[r][i] = 1;

		for (int j = r + 1;j < n;j++)
		{
			if (martrix[j][i] > 1e-6)//СڣΪλΪ0
				for (int g = n;g >= i;g--)
				{
					martrix[j][g] -= martrix[j][i] * martrix[r][g];
				}
		}
		r++;
	}
	//һ鷽
	//ʱֻҪµnеĴ𰸼
	return  0;
	//ȱж޽
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

	cin >> n;
	double** martrix = (double**)malloc(sizeof(double*) * n);
	for (int i = 0;i < n;i++) martrix[i] = (double*)malloc(sizeof(double) * (n + 1));
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j <= n;j++)
		{
			cin >> martrix[i][j];
		}
	}


	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}