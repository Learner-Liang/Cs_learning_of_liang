/*
ã€é¢˜ç›®ã€‘5 å¿«é€Ÿæ’åº
ã€æ•´ä½“ç®—æ³•æ€è·¯ã€‘
æ­¥éª¤1ï¼šè¯»å–è¾“å…¥å¹¶å®Œæˆåˆå§‹åŒ–ã€‚
ç›®çš„ï¼šå°†é¢˜ç›®æ•°æ®è½¬æ¢ä¸ºå¯è®¡ç®—çš„çŠ¶æ€ã€‚
æ­¥éª¤2ï¼šå»ºç«‹æœ¬é¢˜éœ€è¦çš„æ•°æ®ç»“æ„/çŠ¶æ€å®šä¹‰ã€‚
ç›®çš„ï¼šä¸ºåç»­æ ¸å¿ƒç®—æ³•æä¾›æ­£ç¡®çš„ä¿¡æ¯ç»„ç»‡æ–¹å¼ã€‚
æ­¥éª¤3ï¼šæ‰§è¡Œæ ¸å¿ƒç®—æ³•æµç¨‹ï¼ˆè§ä¸‹æ–¹å…³é”®å‡½æ•°æˆ–å¾ªç¯ï¼‰ã€‚
ç›®çš„ï¼šæŒ‰é¢˜æ„é€æ­¥æ±‚è§£å¹¶å¾—åˆ°æœ€ç»ˆç­”æ¡ˆã€‚
æ­¥éª¤4ï¼šè¾“å‡ºç»“æœå¹¶ç»“æŸç¨‹åºã€‚
ç›®çš„ï¼šè¿”å›é¢˜ç›®è¦æ±‚çš„ç»“æœï¼Œå®Œæˆä¸€æ¬¡å®Œæ•´æ±‚è§£ã€‚
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
int check(int* arr, int size)//×¢ÒâsizeµÄ´óĞ¡
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
	//Ò»´ÎÕÒµ½Ò»¶ÔÔªËØ½øĞĞ½»»»£º¼õÉÙÅĞ¶Ï´ÎÊı
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
	quick_sort_v1(arr, l, head);//´ËÊ±headÎªÇ°°ë¶Î×î´óÖµ
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
		//Ò»´ÎÕÒµ½Ò»¶ÔÔªËØ½øĞĞ½»»»£º¼õÉÙÅĞ¶Ï´ÎÊı
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
		quick_sort_v2(arr, l, head);//´ËÊ±headÎªÇ°°ë¶Î×î´ó
		l = head;
	}
}
//Ëã·¨Ê±¼ä¸´ÔÓ¶ÈÓë»ù×¼Ëù´¦µÄÎ»ÖÃÓĞ¹Ø£¬Á½±ßÊıµÄÊıÁ¿½Ó½üµÄ»¯£¬Ê±¼ä¸´ÔÓ¶ÈµÍ
int three_point_select(int a, int b, int c)
{
	//È¡ÖĞ¼äÖµ
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
	while (16 < r - l)//¼«ÖÂÓÅ»¯£ºÔÚÔªËØÔÚ16ÒÔÄÚµÄÊ±ºò¸ÄÓÃ²åÈëÅÅĞò 
	{
		int head = l, tail = r - 1, base = three_point_select(arr[l], arr[r - 1], arr[(l + r) / 2]);
		//Ò»´ÎÕÒµ½Ò»¶ÔÔªËØ½øĞĞ½»»»£º¼õÉÙÅĞ¶Ï´ÎÊı
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
		quick_sort_v3(arr, l, head);//´ËÊ±headÎªÇ°°ë¶Î×î´óÖµ
		l = head;
	}
}
void _quick_sort_v3(int* arr, int l, int r)
{
	quick_sort_v3(arr, l, r);
	//Ö®ºó¾ÍÊÇÎŞ¼à¶½µÄ²åÈëÅÅĞò¡¤

}