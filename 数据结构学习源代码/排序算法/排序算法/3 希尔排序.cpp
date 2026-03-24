#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int check(int* arr, int size);
int* getRandDate(int n);
void shell_sort(int* arr, int l, int r);//1
void shell_sort_hibbard(int* arr, int l, int r);
void Swap(int* n, int* m);
void insert__sort(int* arr, int l, int r, int step)//希尔排序专用的插入排序
{
	int ind = l;//默认第一位已经被排好了
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
	return 0;
}
int check(int* arr, int size)//注意size的大小
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