#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int check(int* arr, int size);
int* getRandDate(int n);
void bubble_sort(int* arr, int l, int r);
void Swap(int* n, int* m);
int main()
{
	int n;
	scanf("%d",n);
	int* arr = getRandDate(n);
	bubble_sort(arr, 0, n);
	check(arr, n);
	return 0;
}
int check(int* arr, int size)//注意size的大小
{
	for (int i = 0;i < size;i++)
	{
		if (arr[i] > arr[i + 1])

		{

			printf("wrong\n", arr[i]);
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
void bubble_sort(int* arr, int l, int r)
{
	for (int i = r - 1;i > l;i--)
	{
		for (int j = l;j < i;j++)
		{
			if (arr[j] > arr[j + 1])Swap(arr + j, arr + j + 1);
		}
	}
	return ;
}