/*
【题目】17  lostcows
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

/*有n只小动物，每只都有一个独特的编号，分别从1到n。现在他们从左到右依次排在一条直线上，顺序是乱的。
​ 现在，我们只知道每个位置前面有几个比他小的数。请你根据给出的信息计算出每个位置上的数是多少。1≤n≤80000。*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define lowbit(x) (x)&(-x)
void _add_(int* c, int x, int k, int n)
{
// 步骤1（代码实现）：读取输入并完成必要初始化。
// 目的：把原始输入转化为程序可处理的数据状态。
// 实现：通过输入语句与初始赋值准备基础变量。
// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
// 目的：为核心转移/搜索/计算过程提供载体。
// 实现：用数组、容器或自定义结构存储中间状态与关系。
// 步骤3（代码实现）：执行核心算法流程。
// 目的：按照题意完成状态转移、搜索或计算求解。
// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	while (x <= n)
	{
		c[x] += k;
		x += lowbit(x);
	}
	

// 步骤4（代码实现）：输出结果并返回。
// 目的：给出最终答案并结束程序执行。
// 实现：调用输出语句打印结果，并通过 return 结束流程。
return;
}
int _query_(int* c, int x)
{
	int sum = 0;
	while (x)
	{
		sum += c[x];
		x -= lowbit(x);
	}
	return sum;
}
int _binary_search(int* c, int k,int n)
{
	int l = 1, r = n, mid;
	while (l < r)
	{
		mid = (l + r) / 2;
		if (_query_(c, mid) < k)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}
int main17()
{
	//从后往前找，找到前缀和与其对应的编号
	int n;
	cin >> n;
	int a[100] = { 0 };
	a[1] = 0;
	for (int i = 2;i <= n;i++)	scanf("%d", a + i);
	int c[100] = { 0 };
	for (int i = 1;i <= n;i++)_add_(c, i, 1, n);
	for (int i = n;i;i--)
	{
		a[i] = _binary_search(c, a[i] + 1,n);
		_add_(c, a[i], -1, n);
	}
	for (int i = 1;i <= n;i++)
		cout << a[i] << endl;
	return 0;
}