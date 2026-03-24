/*
【题目】1 二分查找
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void output(int* arr, int n)
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

	for (int i = 0;i < n;i++)
		printf("%3d", i);
	printf("\n");
	for (int j = 0;j < n;j++)
	{
		printf("%3d", arr[j]);
	}
	printf("\n");

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
}
int binary_search(int* arr, int n, int x)
{
	int head = 0, tail = n - 1;
	while (head <= tail)
	{
		int mid = (head + tail) / 2;
		printf("%d  %d  %d  \n", head, mid, tail);
		if (arr[mid] > x) tail = mid - 1;
		else if (arr[mid] < x) head = mid + 1;
		else return mid;
	}
}
int main1()
{
	srand(time(0));
	//
	int* arr = (int*)malloc(sizeof(int) * 10);
	arr[0] = rand() % 10;
	for (int i = 1;i < 10;i++) arr[i] = rand() % 10 + arr[i - 1];
	output(arr, 10);
	int x;
	while (scanf_s("%d", &x))
	{
		if (x < 0)break;
		int ind = binary_search(arr, 10, x);
		printf("%d\n", ind);
	}
	//
	return 0;
}
//x->y,y->x
//ߵ
//ֲ0000111ģͣmid=tail;1111000ģ:head=mid;
//ҵһ1һ0