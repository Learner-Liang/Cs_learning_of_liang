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
	//一次找到一对元素进行交换：减少判断次数
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
	quick_sort_v1(arr, l, head);//此时head为前半段最大值
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
		//一次找到一对元素进行交换：减少判断次数
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
		quick_sort_v2(arr, l, head);//此时head为前半段最大
		l = head;
	}
}
//算法时间复杂度与基准所处的位置有关，两边数的数量接近的化，时间复杂度低
int three_point_select(int a, int b, int c)
{
	//取中间值
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
	while (16 < r - l)//极致优化：在元素在16以内的时候改用插入排序 
	{
		int head = l, tail = r - 1, base = three_point_select(arr[l], arr[r - 1], arr[(l + r) / 2]);
		//一次找到一对元素进行交换：减少判断次数
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
		quick_sort_v3(arr, l, head);//此时head为前半段最大值
		l = head;
	}
}
void _quick_sort_v3(int* arr, int l, int r)
{
	quick_sort_v3(arr, l, r);
	//之后就是无监督的插入排序·

}