#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void output(int* arr, int n)
{
	for (int i = 0;i < n;i++)
		printf("%3d", i);
	printf("\n");
	for (int j = 0;j < n;j++)
	{
		printf("%3d", arr[j]);
	}
	printf("\n");
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
	//数组
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
	//函数
	return 0;
}
//x->y简单,y->x难
//函数或者单调
//二分查找0000111模型：mid=tail;与1111000模:head=mid;
//找到第一个1与最后一个0