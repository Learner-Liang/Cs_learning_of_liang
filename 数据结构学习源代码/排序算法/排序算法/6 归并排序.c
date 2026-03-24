#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int check(int* arr, int size);
int n;
int* getRandDate(int n);
void Swap(int* n, int* m);
void _merge_sort(int* arr, int l, int r);
void merge_sort(int* arr, int l, int r);
int* temp;
int main()
{
	srand(time(0));
	scanf_s("%d", &n);
	temp = (int*)malloc(sizeof(int) * n);
	int* arr = getRandDate(n);
	int t1 = clock();
	merge_sort(arr, 0, n);
	int t2 = clock();
	check(arr, n);
	printf("%d ms", t2 - t1);
	free(arr);
	free(temp);
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
void Swap(int* n, int* m)
{
	int temp = *n;
	*n = *m;
	*m = temp;
	return;
}
void _merge_sort(int* arr, int l, int r)
{
	if (r - l <= 1)return;
	int mid = (l + r) / 2;
	_merge_sort(arr, l, mid);
	_merge_sort(arr, mid, r);
	int p1 = l, p2 = mid, k = 0;
	while (p1 < mid || p2 < r)
	{
		if (p2 == r || (p1 < mid && arr[p1] < arr[p2]))
		{
			temp[k++] = arr[p1++];
		}
		else
		{
			temp[k++] = arr[p2++];
		}
	}
	for (int i = l;i < r;i++)
		arr[i] = temp[i - l];
	return;
}
void merge_sort(int* arr, int l, int r)
{
	_merge_sort(arr, l, r);
	return;
}