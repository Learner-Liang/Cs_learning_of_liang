/*
【题目】6 奶牛围栏
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
int c, n;
typedef struct point
{
	int x, y;
}point;
point P[505] = { 0 };
int temp[505] = { 0 };
bool check(int l);
bool check_y(int i, int j, int l);
int main()
{
	cin >> c >> n;
	for (int i = 0;i < n;i++)scanf("%d %d", &(P[i].x), &(P[i].y));
	sort(P, P + n, [&](const point a, const point b)->bool {
		if (a.x == b.x)return a.y < b.y;
		else return a.x < b.x;
		});
	int head = 1, tail = 10000, mid;
	while (head < tail)
	{
		mid = (head + tail) / 2;
		if (check(mid))tail = mid;
		else head = mid + 1;
	}
	printf("%d", tail);
	return 0;
}
bool check(int l)
{
	int j = 0;
	for (int i = 0;i < n;i++)
	{
		while (P[i].x - P[j].x >= l)j++;
		if (i - j + 1 >= c)
		{
			if (check_y(j, i, l))return 1;
		}
	}
	return false;
}
bool check_y(int i, int j, int l)
{
	int cnt = 0;
	for (int x = i;x <= j;x++)temp[cnt++] = P[x].y;
	sort(temp, temp + cnt);
	for (int k = c - 1;k < cnt;k++)
	{
		if (temp[k] - temp[k - c + 1] < l)
		{

			return 1;
		}
	}
	return false;
}