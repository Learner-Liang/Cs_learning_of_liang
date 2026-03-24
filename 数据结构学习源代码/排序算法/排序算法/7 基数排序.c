#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
int check(int* arr, int size);
int* getRandDate(int n);
void Swap(int* n, int* m);
void radix_sort(int* arr, int l, int r);
int main()
{
	srand(time(0));
	int* arr = getRandDate(10000);
	int t1 = clock();
	//printf("%d", arr[0]);
	radix_sort(arr, 0, 10000);
	int t2 = clock();
	check(arr, 10000);
	free(arr);
	printf("%d ms", t2 - t1);
	return 0;
}
int check(int* arr, int size)//注意size的大小
{
	size--;
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
//采用二进制
void radix_sort(int* arr, int l, int r)
{
#define K 65636
	int* cnt = (int*)malloc(sizeof(int) * K);
	memset(cnt, 0, sizeof(int) * K);
	int* a = (int*)malloc(sizeof(int) * (r - l));
	//第一轮
	for (int i = l;i < r;i++)cnt[arr[i] % K]++;
	for (int i = 1;i < K;i++)cnt[i] += cnt[i - 1];
	for (int i = r - 1;i >= l;i--)a[--cnt[arr[i] % K]] = arr[i];
	memcpy(arr + l, a, sizeof(int) * (r - l));
	//第二轮
	memset(cnt, 0, sizeof(int) * K);
	for (int i = l;i < r;i++)cnt[arr[i] / K]++;
	for (int i = 1;i < K;i++)cnt[i] += cnt[i - 1];
	for (int i = r - 1;i >= l;i--)
		a[--cnt[arr[i] / K]] = arr[i];
	memcpy(arr + l, a, sizeof(int) * (r - l));
	free(a);
	free(cnt);
	return;
}