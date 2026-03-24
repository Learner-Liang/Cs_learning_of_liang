/*
【题目】22 区间最大公约数
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

/*HZOJ334*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
/*Gcd(a,b)=gcd(a,b-a)=gcd(a-b,b)
gcda,b,c)=gcd(a,b,c-b)=gcd(a,b-a,c-b);
ȵ
*/
//άԼ
#define int long long
int n, m, ans = 0;
int a[100] = { 0 };
int val[405] = { 0 }, c[405] = { 0 };
int gcd(int a, int b)
{
	if (!b)return a;
	return gcd(b, a % b);
}
void UP(int ind);
void build(int ind, int l, int r);
void modify(int ind, int l, int r, int x,int k);
void GCD(int ind,int l,int r,int x, int y);
int query(int ind, int l, int r, int x, int y);
int32_t main()
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

	cin >> n >> m;
	for (int i = 1;i <= n;i++)scanf("%lld", a + i);
	build(1,1,n);
	for (int i = 0,l,r,d;i < m;i++)
	{
		char ch[5];
		scanf("%s", ch);
		scanf("%s", ch);
		if (ch[0] == 'C')
		{
			scanf("%lld%lld%lld", &l, &r, &d);
			modify(1, 1, n, l, d);
			if (r + 1 <= n)modify(1, 1, n, r + 1, -d);
		}
		else
		{
			scanf("%lld %lld", &l, &r);
			ans=query(1, 1, n, 1, l);
			if(l+1<=r)GCD(1,1,n,l + 1, r);
			cout <<abs( ans) << endl;
		}
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
void build(int ind, int l, int r)
{
	if (l == r)
	{
		val[ind] = a[l] - a[l - 1];
		c[ind] = a[l] - a[l - 1];
		return;
	}
	int mid = (l + r) / 2;
	build(ind * 2, l, mid);
	build(ind * 2 + 1, mid + 1, r);
	UP(ind);
	return;
}
void UP(int ind)
{
	val[ind] = val[ind * 2] + val[ind * 2 + 1];
	c[ind] = gcd(c[ind * 2], c[ind * 2 + 1]);
	return;
}
void modify(int ind, int l, int r, int x, int k)
{
	if (l == r)
	{
		val[ind] += k;
		c[ind] += k;
		return;
	}
	int mid = (l + r) / 2;
	if (x <= mid)modify(ind * 2, l, mid, x, k);
	else modify(ind * 2 + 1, mid + 1, r, x, k);
	UP(ind);
	return;
}
void GCD(int ind,int l,int r, int x, int y)
{
	if (x <= l && y >= r)
	{
		ans = gcd(ans, c[ind]);
		return;
	}
	int mid = (l + r) / 2;
	if (x <= mid)GCD(ind * 2, l, mid, x, y);
	if (y >mid)GCD(ind * 2 + 1, mid + 1, r, x, y);
	return;
}
int query(int ind, int l, int r, int x, int y)
{
	
	if (x <= l && y >= r)return val[ind];
	int sum = 0;
	int mid = (l + r) / 2;
	if (x <= mid)sum += query(ind * 2, l, mid, x, y);
	if (y > mid)sum += query(ind * 2 + 1, mid + 1, r, x, y);

	return sum;
}