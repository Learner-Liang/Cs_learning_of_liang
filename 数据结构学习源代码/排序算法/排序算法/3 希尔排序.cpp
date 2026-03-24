/*
【题目】3 希尔排序
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
void shell_sort(int* arr, int l, int r);//1
void shell_sort_hibbard(int* arr, int l, int r);
void Swap(int* n, int* m);
void insert__sort(int* arr, int l, int r, int step)//ϣרõĲ
{
	int ind = l;//ĬϵһλѾź
	for (int i = l + step;i < r;i += step)if (arr[ind] > arr[i])ind = i;
	while (ind > l)
	{
		Swap(arr + ind, arr + ind - step);
		ind -= step;
	}

	for (int i = l + 2 * step;i < r;i += step)
	{
		ind = i;
		while (arr[ind] < arr[ind - step])Swap(&arr[ind], &arr[ind - step]), ind -= step;
	}
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
	scanf_s("%d", &n);
	int* arr = getRandDate(n);
	int t1 = clock();
	shell_sort(arr, 0, n);
	int t2 = clock();
	printf("%d\n", t2 - t1);
	check(arr, n);
	free(arr);
	arr = getRandDate(n);
	t1 = clock();;
	shell_sort_hibbard(arr, 0, n);
	t2 = clock();
	check(arr, n);
	printf("%d\n", t2 - t1);
	//for (int i = 0;i < n;i++)printf("%d ", arr[i]);

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
int check(int* arr, int size)//עsizeĴС
{
	size--;
	for (int i = 0;i < size;i++)
	{
		if (arr[i] > arr[i + 1])

		{
			printf("wrong\n");
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
void shell_sort(int* arr, int l, int r)
{
	int k = 2, n = (r - l), step;
	do
	{
		step = n / k == 0 ? 1 : n / k;
		for (int i = l, I = l + step;i < I;i++)insert__sort(arr, i, r, step);
		k *= 2;
	} while (step != 1);
	return;
}
void Swap(int* n, int* m)
{
	int temp = *n;
	*n = *m;
	*m = temp;
	return;
}
void shell_sort_hibbard(int* arr, int l, int r)
{
	int step = 1, n = (r - l);
	while (step <= n / 2)step = step * 2 + 1;
	do
	{
		step /= 2;
		for (int i = l, I = l + step;i < I;i++)insert__sort(arr, i, r, step);
	} while (step >= 1);
	return;
}