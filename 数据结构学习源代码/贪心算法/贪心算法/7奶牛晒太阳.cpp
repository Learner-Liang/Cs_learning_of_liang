/*
【题目】7奶牛晒太阳
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
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
typedef struct Scream {
	int power, num;
}scream;
typedef struct cows
{
	int l, r;
}cows;
bool cmp1(scream& a, scream& b)
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


	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return a.power < b.power;
}

bool cmp2(cows& a, cows& b)
{
	if (a.r == b.r) return a.l < b.l;
	return a.r < b.r;
}
int main7()
{
	//С߶Ҷ˴СҲ
	cows arr1[2504] = { 0 };
	scream arr2[2504] = { 0 };
	int c, l;
	cin >> c >> l;
	for (int i = 0;i < c;i++)
	{
		scanf("%d%d", &arr1[i].l, & arr1[i].r);
	}
	for (int i = 0;i < l;i++)
	{
		scanf("%d%d", &arr2[i].power, &arr2[i].num);
	}
	sort(arr1, arr1 + c, cmp2);
	sort(arr2, arr2 + l, cmp1);
	int ans = 0;
	for (int i = 0;i < c;i++)
	{
		//
		/*while (arr2[count].num == 0)count++;
		if (arr1[i].r < arr2[count].power)continue;
		if (arr1[i].l <= arr2[count].power)
		{
			ans++;
			arr2[count].num--;
		}
		else count++;*/
		for (int j = 0;j < l;j++)
		{
			if (arr2[j].num == 0)continue;;
			if (arr1[i].l <= arr2[j].power && arr1[i].r >= arr2[j].power)
			{
				arr2[j].num--;
				ans += 1;
				break;
			}
		}
	}
	cout << ans;
	return 0;
}