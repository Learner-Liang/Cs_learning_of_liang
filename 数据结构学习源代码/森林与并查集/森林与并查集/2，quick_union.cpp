/*
【题目】2，quick_union
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

// quick_union
// ӽڵ㶼ֱӻ߼ָڵ㣬Ǹڵָӽڵ㣬ӽڵָ򸸽ڵ
//ϲǽһΪһ
//ı丸ڵָ±һʼֵΪԼ±ֵ֮Լֵ޸Ϊӽڵ±ֵ
//ڵĸڵԼֵΪԼ±
#include <iostream>
using namespace std;
#define max 10005
int color[max] = { 0 };
int size[max + 5];//ÿڵĽڵʼΪ1
void init(int);
int find(int n);//ظڵ±
int merge(int a, int b);
void output(int n);
void output_line(int i);
//鼯İŻߺͽڵ
//·ѹŻеĽڵڸڵ棬
//findɣڲѯаиڵȥquick_find
int main()
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

	int n, a, b;
	cin >> n;
	init(n);
	while (scanf_s("%d %d", &a, &b))
	{
		if (merge(a, b))
			printf("merge %d with %d.\n", a, b);
		output(n);
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
void init(int n)
{
	for (int i = 0;i < n;i++)
	{
		color[i] = i;
		size[i] = 1;
	}
	return ;
}
int find(int n)
{
	if (color[n] == n)return n;
	return find(color[n]);
}
int merge(int a, int b)
{
	int aa = find(a), bb = find(b);
	if (aa == bb)return 0;
	color[bb] = aa;
	return 1;
}
void output(int n)
{
	for (int i = 0;i < n;i++)
	{
		output_line(i);
	}
}
void output_line(int i)
{
	while (color[i] != i)
	{
		printf("(%3d:%d)->", i, color[i]);
		i = color[i];
	}
	printf("(%3d:%d)\n", i, i);
}
//Ż
int size[max + 5];//ÿڵĽڵʼΪ1
int merge1(int a, int b)
{
	int aa = find(a), bb = find(b);
	if (aa == bb)return 0;
	//ڵĵ
	if (size[a] > size[b])
	{
		size[aa] += size[bb];
		color[bb] = aa;
	}
	else {
		size[bb] += size[a];
		color[aa] = bb;
	}
	return 1;
}
//·ѹŻ
int find1(int n)
{
	if (color[n] == n)return n;
	color[n] = find(color[n]);
	return color[n];
}