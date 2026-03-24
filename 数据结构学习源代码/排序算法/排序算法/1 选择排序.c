#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int check(int* arr, int size);
int* getRandDate(int n);
void selection_sort(int* arr, int l, int r);//选择排序
int main()
{
	srand(time(0));
	int* arr = getRandDate(10000);
	int t1 = clock();
	selection_sort(arr, 0, 10000);
	int t2=clock();
	check(arr, 9999);
	printf("%d ms\n", t2 - t1);
	free(arr);
	return 0;
}
int check(int* arr, int size)//注意size的大小
{
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
void selection_sort(int* arr, int l, int r)//左闭右开
{
	for (int i = l, I = r - 1;i < I;i++)
	{
		int ind = i;
		for (int j = i + 1;j < r;j++)
		{
			if (arr[j] < arr[ind]) ind = j;
		} 
		int temp = arr[ind];
		arr[ind] = arr[i];
		arr[i] = temp;
	}
	return;
}