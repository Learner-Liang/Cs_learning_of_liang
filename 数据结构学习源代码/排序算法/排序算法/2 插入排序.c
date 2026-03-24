#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int check(int* arr, int size);
int* getRandDate(int n);
void insert_sort(int* arr, int l, int r);//插入算法
void insert__sort(int* arr, int l, int r);//优化的插入算法
void Swap(int* n, int *m);
int main()
{
	int n;
	scanf_s("%d", &n);
	int* arr = getRandDate(n);
	insert_sort(arr, 0, n);
	check(arr, n);
	insert__sort(arr, 0, n);
	check(arr, n);
}
int check(int* arr, int size)
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
void insert_sort(int* arr, int l, int r)
{
	int ind = l+1;//默认第一位已经被排好了
	for (int i = ind;i < r;i++)
	{
		ind = i;
		while (ind > l && arr[ind] < arr[ind - 1])swap(arr[ind], arr[ind - 1]), ind--;
	}
}
void insert__sort(int* arr, int l, int r)//优化的插入算法
{
	int ind = l;//默认第一位已经被排好了
	for (int i = l + 1;i < r;i++)if (arr[ind] > arr[i])ind = i;
	while (ind > l)
	{
		swap(arr + ind, arr + ind - 1);
		ind--;
	}

	for (int i = l+1;i < r;i++)
	{
		ind = i;
		while (arr[ind] < arr[ind - 1])swap(arr[ind], arr[ind - 1]), ind--;
	}
}
void Swap(int* n,int* m)
{
	int temp = *n;
	*n = *m;
	*m = temp;
	return;
}
