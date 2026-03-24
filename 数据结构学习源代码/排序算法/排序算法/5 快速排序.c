/*
【题目】5 快速排序
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
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行状态更新，逐步逼近最优解/可行解。
// 目的：把局部决策累积为全局答案；若是 DP，本质是“已知子问题 -> 当前问题”的转移。
// 关键代码说明：max/min/松弛/合并等更新语句是核心；它们对应题目中的数学关系或最优性原理。

// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

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
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
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