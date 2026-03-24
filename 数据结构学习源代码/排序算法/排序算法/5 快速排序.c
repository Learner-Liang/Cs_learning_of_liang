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
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	srand(time(0));
	int n;
	scanf_s("%d", &n);
	int* arr = getRandDate(n);
	arr = getRandDate(n);
	int t1 = clock();
	quick_sort(arr, 0, n);
	int t2 = clock();
	check(arr, n);
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