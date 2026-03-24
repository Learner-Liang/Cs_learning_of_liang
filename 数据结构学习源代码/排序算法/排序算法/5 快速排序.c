/*
【题目】5 快速排序
【整体算法思路】
步骤1：读取输入并完成初始化。先把题目给的数字/字符串准确放进变量。
目的：只有输入含义搞清楚，后面 for/while 的边界与数组下标才不会写错。
步骤2：建立数据结构/状态定义（尤其是 DP 的 dp[i][j] 到底表示什么）。
目的：把“题目文字”翻译成“程序状态”；定义不清，转移方程一定写不对。
步骤3：执行核心算法（循环/递归/搜索/转移），把子问题答案逐步合成总答案。
目的：每一轮循环都要回答“我现在在解决哪个子问题，为什么这样更新是正确的”。
步骤4：输出结果并结束程序。输出下标必须和状态定义一一对应。
目的：返回题目要求的结果，完成一次完整求解。
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int check(int* arr, int size);
int* getRandDate(int n);
void Swap(int* n, int* m);
void quick_sort(int* arr, int l, int r);
void quick_sort_v1(int* arr, int l, int r);
void quick_sort_v2(int* arr, int l, int r);
void quick_sort_v3(int* arr, int l, int r);
void _quick_sort_v3(int* arr, int l, int r);
int three_point_select(int a, int b, int c);
int main()
{
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行更新，把“已知子问题”推到“当前问题”。
// 目的：让小问题先解、大问题后解；若是 DP，要先说清状态定义，再写状态转移方程。
// 关键代码说明：max/min/松弛语句对应数学关系；循环顺序和 if 条件共同保证“不会漏解、不会重算、不会越界”。

// 步骤3细化（判断条件解释）：这个 if/while 是“题目约束”的程序化表达，用来过滤非法状态。
// 为什么这么写：若不先判断就更新，常见后果是越界、重复使用元素或把不可能状态算进去。

	srand(time(0));
	int n;
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	scanf_s("%d", &n);
	int* arr = getRandDate(n);
	arr = getRandDate(n);
	int t1 = clock();
	quick_sort(arr, 0, n);
	int t2 = clock();
	check(arr, n);
	
	// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
	printf("%dms\n", t2 - t1);
	free(arr);
	arr = getRandDate(n);
	t1 = clock();
	quick_sort_v1(arr, 0, n);
	t2 = clock();
	check(arr, n);
	printf("%dms\n", t2 - t1);
	free(arr);
	arr = getRandDate(n);
	t1 = clock();
	quick_sort_v2(arr, 0, n);
	t2 = clock();
	check(arr, n);
	printf("%dms\n", t2 - t1);
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return 0;
}
int check(int* arr, int size)//עsizeĴС
{
	size--;
	
	// 步骤3细化（核心循环解释）：for/while 的顺序不是随便写的，它决定“先用哪些已知结果”。
	// 顺序背后的原理：0/1 背包常用倒序防止同一物品被重复选；图最短路按当前最优点扩展才满足贪心前提。
	for (int i = 0;i < size;i++)
	{
		if (arr[i] > arr[i + 1])

		{

			printf("wrong\n", arr[i]);
			//for (int j = 0;j <= size;j++)printf("%d  ", arr[j]);
			return 0;
		}
	}
	printf("True\n");
	return 1;
}
int* getRandDate(int n)
{
	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0;i < n;i++)
	{
		arr[i] = rand() % 10000;
	}
	return arr;
}

void Swap(int* n, int* m)
{
	int temp = *n;
	*n = *m;
	*m = temp;
	return;
}
void quick_sort(int* arr, int l, int r)
{
	if (r - l < 2)
	{
		return;
	}
	if (r - l == 2)
	{
		if (arr[l] > arr[l + 1])Swap(arr + l, arr + l + 1);
		return;
	}
	int head = l, tail = r - 1;
	int base = arr[l];
	while (head < tail)
	{
		while (head < tail && arr[tail] >= base)tail--;
		if (head < tail)arr[head++] = arr[tail];
		while (head < tail && arr[head] <= base)head++;
		if (head < tail)arr[tail--] = arr[head];
	}
	arr[tail] = base;
	quick_sort(arr, l, head);
	quick_sort(arr, head + 1, r);
	return;
}
void quick_sort_v1(int* arr, int l, int r)
{
	if (r - l <= 2)
	{
		if (r - l <= 1)
			return;
		if (arr[r - 1] < arr[l])
		{
			Swap(arr + r - 1, arr + l);
		}
		return;
	}
	int head = l, tail = r - 1, base = three_point_select(arr[l], arr[r - 1], arr[(l + r) / 2]);
	//һҵһԪؽнжϴ
	do {
		while (arr[head] < base)head++;
		while (arr[tail] > base) tail--;
		if (head <= tail)
		{
			Swap(arr + head, arr + tail);
			head++, tail--;
		}
	} while (head <= tail);
	//arr[head] = base;
	quick_sort_v1(arr, l, head);//ʱheadΪǰֵ
	quick_sort_v1(arr, head, r);
}
void quick_sort_v2(int* arr, int l, int r)
{
	while (l < r)
	{
		if (r - l <= 2)
		{
			if (r - l <= 1)
				return;
			if (arr[r - 1] < arr[l])
			{
				Swap(arr + r - 1, arr + l);
			}
			return;
		}
		int head = l, tail = r - 1, base = three_point_select(arr[l], arr[r - 1], arr[(l + r) / 2]);
		//һҵһԪؽнжϴ
		do {
			while (arr[head] < base)head++;
			while (arr[tail] > base) tail--;
			if (head <= tail)
			{
				Swap(arr + head, arr + tail);
				head++, tail--;
			}
		} while (head <= tail);
		//arr[head] = base;
		quick_sort_v2(arr, l, head);//ʱheadΪǰ
		l = head;
	}
}
//㷨ʱ临Ӷ׼λйأӽĻʱ临Ӷȵ
int three_point_select(int a, int b, int c)
{
	//ȡмֵ
	if (a > b)Swap(&a, &b);
	if (a > c)Swap(&a, &c);
	if (b > c)Swap(&a, &b);
	return b;
}
void quick_sort_v3(int* arr, int l, int r)
{
	if (r - l <= 2)
	{
		if (r - l <= 1)
			return;
		if (arr[r - 1] < arr[l])
		{
			Swap(&arr[r - 1], &arr[l]);
		}
		return;
	}
	while (16 < r - l)//ŻԪ16ڵʱò 
	{
		int head = l, tail = r - 1, base = three_point_select(arr[l], arr[r - 1], arr[(l + r) / 2]);
		//һҵһԪؽнжϴ
		do {
			while (arr[head] < base)head++;
			while (arr[tail] > base) tail--;
			if (head <= tail)
			{
				Swap(&arr[head], &arr[tail]);
				head++, tail--;
			}
		} while (head <= tail);
		arr[head] = base;
		quick_sort_v3(arr, l, head);//ʱheadΪǰֵ
		l = head;
	}
}
void _quick_sort_v3(int* arr, int l, int r)
{
	quick_sort_v3(arr, l, r);
	//֮޼ලĲ

}