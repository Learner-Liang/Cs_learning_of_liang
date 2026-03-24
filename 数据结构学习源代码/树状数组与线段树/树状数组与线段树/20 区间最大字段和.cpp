/*
【题目】20 区间最大字段和
【整体算法思路】
步骤1：读取输入并完成初始化。先把题目给的数字/字符串准确放进变量。
目的：只有输入含义搞清楚，后面 for/while 的边界与数组下标才不会写错。
步骤2：建立数据结构/状态定义（尤其是 DP 的 dp[i][j] 到底表示什么）。
目的：把“题目文字”翻译成“程序状态”；定义不清，转移方程一定写不对。
步骤3：执行核心算法（循环/递归/搜索/转移），把子问题答案逐步合成总答案。
目的：每一轮循环都要回答“我现在在解决哪个子问题，为什么这样更新是正确的”。
步骤4：输出结果并结束程序。输出下标必须和状态定义一一对应。
目的：返回题目要求的结果，完成一次完整求解。
*/

/*​ 给定长度为N的数列A，以及M条指令 (N≤500000, M≤100000)，每条指令可能是以下两种之一：

​ “2 x y”，把 A[x] 改成 y。

// 步骤3细化（判断条件解释）：这个 if/while 是“题目约束”的程序化表达，用来过滤非法状态。
// 为什么这么写：若不先判断就更新，常见后果是越界、重复使用元素或把不可能状态算进去。

​ “1 x y”，查询区间 [x,y] 中的最大连续子段和，即max(x≤l≤r≤y)∑ri=l
A[i]。*/
//一个节点中维护三个最值，就是左节点中最大值和以左节点区间最后一位向前的最大值，还有右
//右区间维护最左的一个点
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define MID int mid=(l+r)>>1
int _cnt_ = 2, t1 = 0, t2 = 1, flag = 1;//注意，树的遍历区间是从左逐步到右，up更新操作类似与区间合并
//如果是第一个节点，直接赋值给t1即可，如不是，则向上更新
struct node
{
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行更新，把“已知子问题”推到“当前问题”。
// 目的：让小问题先解、大问题后解；若是 DP，要先说清状态定义，再写状态转移方程。
// 关键代码说明：max/min/松弛语句对应数学关系；循环顺序和 if 条件共同保证“不会漏解、不会重算、不会越界”。

// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。

	int l, r, sum;
	int m, lm, rm;
};
void swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return;
}
void query_max(node* tree, int ind, int l, int r, int x, int y);
void build_tree_max(int* a, node* tree, int ind, int l, int r);
void updata_max(node* tree,int a, int b, int c);
void modify_max(node* tree, int ind,int l, int r, int x, int y);
int main20()
{
	int n, m;
	scanf("%d%d", &n, &m);
	int num[100] = { 0 };
	node tree[100];
	
	// 步骤3细化（核心循环解释）：for/while 的顺序不是随便写的，它决定“先用哪些已知结果”。
	// 顺序背后的原理：0/1 背包常用倒序防止同一物品被重复选；图最短路按当前最优点扩展才满足贪心前提。
	for (int i = 1;i <= n;i++)scanf("%d", num + i);
	build_tree_max(num, tree, 2,  1, n);
	for (int i = 1,k,x,y;i <= m;i++)
	{
		scanf("%d%d%d", &k, &x, &y);
		if (k == 1)
		{
			if (x > y)swap(x, y);
			flag = 1;
			query_max(tree, 2, 1, n, x, y);
			
			// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
			cout << tree[t2].m << endl;
		}
		else
		{
			modify_max(tree, 2, 1, n, x, y);
		}
	}
	return 0;
}
void query_max(node* tree, int ind, int l, int r, int x, int y)
{
	if (x <= l && y >= r)
	{
		if (flag)
		{
			tree[t1] = tree[ind];
			flag = 0;
		}
		else
		{
			updata_max(tree, t1, t2, ind);
		}
		swap(t1, t2);
		return;
	}
	MID;
	if(x<=mid)query_max(tree, tree[ind].l, l, mid, x, y);
	if(y>mid)query_max(tree, tree[ind].r, mid + 1, r, x, y);

	return;
}
void build_tree_max(int* a, node* tree, int ind, int l, int r)
{
	tree[ind].l = ++_cnt_;
	tree[ind].r = ++_cnt_;
	if (l == r)
	{
		tree[ind].sum = tree[ind].lm = tree[ind].rm = tree[ind].m=a[l];
		return;
	}
	MID;
	build_tree_max(a, tree, tree[ind].l, l, mid);
	build_tree_max(a, tree, tree[ind].r, mid + 1, r);
	updata_max(tree,ind, tree[ind].l, tree[ind].r);
	return;
}
void updata_max(node* tree,int a, int b, int c)
{
	tree[a].sum = tree[b].sum + tree[c].sum;
	tree[a].lm = max(tree[b].lm, tree[b].sum + tree[c].lm);
	tree[a].rm = max(tree[c].rm, tree[c].sum + tree[b].rm);
	tree[a].m = max(tree[b].m, tree[c].m);
	tree[a].m = max(tree[a].m, tree[b].rm+ tree[c].lm);
	return;
}
void modify_max(node* tree,int ind, int l, int r, int x, int y)
{
	if (l == r)
	{
		tree[ind].sum = tree[ind].m = tree[l].lm = tree[l].rm = y;
		//cout << l<<"xiugai"<<tree[ind].m << endl;
		return;
	}
	MID;
	if (x <= mid)modify_max(tree, tree[ind].l, l, mid, x, y);
	else modify_max(tree,tree[ind].r, mid + 1,r, x, y);
	updata_max(tree,ind, tree[ind].l, tree[ind].r);
	return;
}