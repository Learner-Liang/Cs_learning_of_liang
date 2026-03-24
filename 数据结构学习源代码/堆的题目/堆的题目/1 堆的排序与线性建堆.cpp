/*
【题目】1 堆的排序与线性建堆
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

#include <iostream>
#include <time.h>
using namespace std;
int n;
int* getRand(int n);
void downmain(int* a, int f);
int check(int* a, int f);
int main()
{
	srand(time(0));
	cin >> n;
	int* a = getRand(n);
	for (int i = n - 1;i >= 0;i--)
	{
		downmain(a, i);
	}
	if (check(a, 0))printf("OK\n");
	else printf("FALSE\n");
	return 0;
}
int* getRand(int n)
{
	int* a = (int*)malloc(sizeof(int) * n);
	for (int i = 0;i < n;i++)a[i] = rand() % 10000;
	return a;
}
void downmain(int* a, int f)
{
	if ((f*2+1)>=n)return;
	int ind = 0;
	if ((f*2+2==n)||a[f * 2 + 1] > a[f * 2 + 2])ind = f * 2 + 1;
	else ind = 2 * f + 2;
	if (a[f] < a[ind])
	{
		int temp = a[f];
		a[f] = a[ind];
		a[ind] = temp;
		downmain(a, ind);
	}
	return;
}
int check(int* a, int f)
{
	if ((2 * f + 1) >= n)return 1;
	int l = 2 * f + 1, r = 2 * f + 2;
	if (a[f] < a[l])return 0;
	if (r < n && a[f] < a[r])return 0;
	return check(a, l) && check(a, r);
}